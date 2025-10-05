/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:15:00 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:28:18 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	handle_quotes(const char *input, int i, char **out, t_gc *gc)
{
	char	quote;
	int		start;
	int		len;

	quote = input[i++];
	start = i;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] != quote)
		return (-1);
	len = i - start;
	*out = gc_malloc(gc, len + 1);
	if (!*out)
		return (-1);
	ft_memcpy(*out, &input[start], len);
	(*out)[len] = '\0';
	return (i + 1);
}

int	append_processed_segment(char **result, const char *segment,
									t_shell *shell)
{
	*result = gc_realloc(shell->gc, *result,
			ft_strlen(*result) + ft_strlen(segment) + 1);
	if (!*result)
		return (0);
	ft_strcat(*result, segment);
	return (1);
}

int	handle_double_quotes(const char *input, int *i, t_collector_state *state)
{
	char	*segment;
	char	*to_append;
	int		new_i;

	new_i = handle_quotes(input, *i, &segment, state->shell->gc);
	if (new_i == -1)
	{
		state->shell->exit_status = 2;
		return (0);
	}
	if (state->in_heredoc)
	{
		state->shell->quoted = 1;
		to_append = expand_variables(segment, state->shell, 0);
	}
	else
		to_append = expand_variables(segment, state->shell, 1);
	if (!to_append)
		return (1);
	if (!append_processed_segment(state->result, to_append, state->shell))
		return (0);
	*i = new_i;
	if (to_append[0] == '\0')
		state->mark_empty = 1;
	return (1);
}

int	handle_single_quotes(const char *input, int *i, t_collector_state *state)
{
	int		start;
	char	*segment;
	char	*to_append;
	int		new_i;

	start = *i;
	new_i = handle_quotes(input, *i, &segment, state->shell->gc);
	if (new_i == -1)
		return (0);
	if (state->in_heredoc)
	{
		state->shell->quoted = 1;
		to_append = segment;
	}
	else
		to_append = segment;
	if (!to_append)
		return (0);
	if (!append_processed_segment(state->result, to_append, state->shell))
		return (0);
	*i = new_i;
	if (to_append[0] == '\0')
		state->mark_empty = 1;
	return (1);
}
