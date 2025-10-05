/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:42:34 by omadali           #+#    #+#             */
/*   Updated: 2025/07/04 16:42:34 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lexer.h"

static int	handle_heredoc(t_tokenizer_state *state, int *is_next_heredoc)
{
	skip_spaces(state->input, state->i);
	*(state->in_heredoc) = 1;
	*is_next_heredoc = 1;
	return (1);
}

static int	handle_word(t_tokenizer_state *state, t_shell *shell,
		int *is_next_heredoc)
{
	char	*word;

	if (*is_next_heredoc)
	{
		word = collect_word_segments(state->input, state->i,
				shell, *(state->in_heredoc));
		*is_next_heredoc = 0;
	}
	else
		word = collect_word_segments(state->input, state->i,
				shell, *(state->in_heredoc));
	if (!word)
	{
		if (shell->syntax_error)
			return (0);
		return (1);
	}
	add_token(state, word, T_WORD, shell->gc);
	*(state->in_heredoc) = 0;
	return (1);
}

static int	process_token_segment(t_tokenizer_state *state, t_shell *shell)
{
	static int	is_next_heredoc = 0;

	if (handle_operator(state->input, state->i, state, shell))
	{
		if (*(state->i) >= 2 && state->input[*(state->i)]
			&& state->input[*(state->i) - 1] == '<'
			&& state->input[*(state->i) - 2] == '<')
		{
			return (handle_heredoc(state, &is_next_heredoc));
		}
		*(state->in_heredoc) = 0;
		return (1);
	}
	return (handle_word(state, shell, &is_next_heredoc));
}

t_token	*tokenize(char *input, t_shell *shell)
{
	t_tokenizer_state	state;
	int					i;
	int					in_heredoc;
	t_token				*tokens;

	i = 0;
	in_heredoc = 0;
	tokens = NULL;
	state.input = input;
	state.i = &i;
	state.tokens = &tokens;
	shell->tokens = state.tokens;
	state.in_heredoc = &in_heredoc;
	while (state.input[*(state.i)])
	{
		skip_spaces(state.input, state.i);
		if (!state.input[*(state.i)])
			break ;
		if (!process_token_segment(&state, shell))
			return (NULL);
	}
	return (tokens);
}
