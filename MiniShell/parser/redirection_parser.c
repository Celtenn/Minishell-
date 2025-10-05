/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:36:07 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parser.h"
#include <unistd.h>

t_redir	*add_redir_gc(t_redir **head, t_redir_info *info, t_gc *gc)
{
	t_redir	*new;
	t_redir	*tmp;

	new = gc_malloc(gc, sizeof(t_redir));
	if (!new)
		return (NULL);
	new->filename = gc_strdup(gc, info->filename);
	new->type = info->type;
	new->quoted_delim = info->quoted;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

static void	create_and_add_redir(t_token *redir_op, t_token *filename_tok,
								t_cmd *cmd, t_shell *shell)
{
	t_redir_info	info;

	if (!filename_tok || !filename_tok->value)
		return ;
	info.filename = filename_tok->value;
	info.type = redir_op->type;
	info.quoted = 0;
	add_redir_gc(&cmd->redirs, &info, shell->gc);
	if (filename_tok->in_herodocc && info.filename != filename_tok->value)
		free(info.filename);
}

int	handle_redirection(t_token **tok, t_cmd *cmd, t_shell *shell)
{
	t_token	*next;

	next = (*tok)->next;
	if (!next || next->type != T_WORD || !next->value || !*next->value)
	{
		write(2, "minishell: syntax error near ", 29);
		write(2, "unexpected token `newline'\n", 27);
		return (0);
	}
	create_and_add_redir(*tok, next, cmd, shell);
	*tok = (*tok)->next;
	return (1);
}
