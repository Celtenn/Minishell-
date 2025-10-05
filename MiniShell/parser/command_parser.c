/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:34:02 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parser.h"
#include <unistd.h>

static int	check_pipe_syntax(t_token *tok)
{
	if (!tok->next || tok->next->type == T_PIPE)
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		return (0);
	}
	return (1);
}

static int	handle_pipe_token(t_token **tok_ptr, t_cmd *cmd)
{
	if (*tok_ptr && (*tok_ptr)->type == T_PIPE)
	{
		if (!check_pipe_syntax(*tok_ptr))
			return (0);
		cmd->pipe_next = 1;
		*tok_ptr = (*tok_ptr)->next;
	}
	return (1);
}

static int	process_command_tokens(t_token **current, t_cmd *cmd,
			t_shell *shell)
{
	t_token	*tok;
	int		i;

	tok = *current;
	i = 0;
	while (tok && tok->type != T_PIPE)
	{
		if (tok->type == T_WORD)
			cmd->argv[i++] = gc_strdup(shell->gc, tok->value);
		else if (tok->type >= T_REDIR_IN && tok->type <= T_HEREDOC)
		{
			if (!handle_redirection(&tok, cmd, shell))
				return (0);
		}
		tok = tok->next;
	}
	cmd->argv[i] = NULL;
	if (!handle_pipe_token(&tok, cmd))
		return (0);
	*current = tok;
	return (1);
}

t_cmd	*parse_single_command(t_token **current, t_shell *shell)
{
	t_token	*tok;
	t_cmd	*cmd;
	int		arg_count;

	tok = *current;
	if (!tok || tok->type == T_PIPE)
	{
		if (tok)
		{
			write(2, "minishell: syntax error near unexpected token `", 47);
			write(2, tok->value, ft_strlen(tok->value));
			write(2, "'\n", 2);
		}
		else
			write(2, "syntax error near unexpected token `newline'\n", 46);
		return (NULL);
	}
	arg_count = count_args(tok);
	cmd = gc_malloc(shell->gc, sizeof(t_cmd));
	cmd->argv = gc_malloc(shell->gc, sizeof(char *) * (arg_count + 1));
	cmd->redirs = NULL;
	cmd->pipe_next = 0;
	if (!process_command_tokens(current, cmd, shell))
		return (NULL);
	return (cmd);
}
