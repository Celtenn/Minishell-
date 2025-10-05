/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:33:29 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parser.h"
#include <unistd.h>

void	clear_redirs(t_redir *r)
{
	t_redir	*curr;

	curr = r;
	while (curr)
	{
		if (curr->type == T_HEREDOC)
			if (curr->heredoc_fd != -1)
				close(curr->heredoc_fd);
		curr = curr->next;
	}
}

void	clear_cmd_list(t_list *cmds)
{
	t_list	*curr;
	t_cmd	*cmd;

	curr = cmds;
	while (curr)
	{
		cmd = (t_cmd *)curr->content;
		clear_redirs(cmd->redirs);
		curr = curr->next;
	}
}
