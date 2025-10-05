/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:15:00 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:27:55 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lexer.h"

static int	handle_redirection_operator(char *input, int *i,
		t_tokenizer_state *fafa, t_shell *shell)
{
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		add_token(fafa, ">>", T_APPEND, shell->gc);
		(*i) += 2;
		return (1);
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		add_token(fafa, "<<", T_HEREDOC, shell->gc);
		(*i) += 2;
		return (1);
	}
	else if (input[*i] == '>')
	{
		add_token(fafa, ">", T_REDIR_OUT, shell->gc);
		(*i)++;
		return (1);
	}
	else if (input[*i] == '<')
	{
		add_token(fafa, "<", T_REDIR_IN, shell->gc);
		(*i)++;
		return (1);
	}
	return (0);
}

int	handle_operator(char *input, int *i,
		t_tokenizer_state *nana, t_shell *shell)
{
	if (input[*i] == '|')
	{
		add_token(nana, "|", T_PIPE, shell->gc);
		(*i)++;
		return (1);
	}
	return (handle_redirection_operator(input, i, nana, shell));
}
