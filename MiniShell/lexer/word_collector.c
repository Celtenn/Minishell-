/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_collector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:15:00 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:29:09 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lexer.h"
#include "../headers/minishell.h"

static int	process_unquoted_for_expansion(const char *input, int start,
										int len, t_collector_state *state)
{
	char	*segment;
	char	*expanded;

	segment = gc_malloc(state->shell->gc, len + 1);
	if (!segment)
		return (0);
	ft_memcpy(segment, &input[start], len);
	segment[len] = '\0';
	if (state->in_heredoc)
		expanded = expand_variables(segment, state->shell, 0);
	else
		expanded = expand_variables(segment, state->shell, 1);
	if (!expanded)
		return (1);
	return (append_processed_segment(state->result, expanded, state->shell));
}

int	handle_unquoted_segment(const char *input, int *i,
							t_collector_state *state)
{
	int		start;

	start = *i;
	while (input[*i] && !ft_isspace((unsigned char)input[*i])
		&& !is_special(input[*i]) && input[*i] != '"' && input[*i] != '\'')
		(*i)++;
	return (process_unquoted_for_expansion(input, start, *i - start,
			state));
}

static int	collect_word_loop(const char *input,
		int *i, t_collector_state *state)
{
	int	success;

	success = 1;
	while (success && input[*i] && !ft_isspace((unsigned char)input[*i])
		&& !is_special(input[*i]))
	{
		if (input[*i] == '"')
			success = handle_double_quotes(input, i, state);
		else if (input[*i] == '\'')
			success = handle_single_quotes(input, i, state);
		else
			success = handle_unquoted_segment(input, i, state);
	}
	return (success);
}

char	*collect_word_segments(const char *input, int *i,
							t_shell *shell, int in_heredoc)
{
	t_collector_state	state;
	int					success;

	state.result = gc_malloc(shell->gc, sizeof(char *));
	if (!state.result)
		return (NULL);
	*(state.result) = gc_strdup(shell->gc, "");
	if (!*(state.result))
		return (NULL);
	state.shell = shell;
	state.in_heredoc = in_heredoc;
	state.shell->quoted = 0;
	state.mark_empty = 0;
	success = collect_word_loop(input, i, &state);
	if (!success)
	{
		shell->exit_status = 2;
		shell->syntax_error = 1;
		return (NULL);
	}
	if (*(state.result)[0] == '\0' && state.mark_empty == 0)
		return (NULL);
	return (*(state.result));
}
