/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:39:52 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>

static int	open_redirection(t_redir *redir)
{
	int	fd;

	if (redir->type == T_REDIR_IN)
		fd = open(redir->filename, O_RDONLY);
	else if (redir->type == T_REDIR_OUT)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == T_APPEND)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == T_HEREDOC)
		fd = redir->heredoc_fd;
	else
		fd = -1;
	return (fd);
}

int	apply_redirections(t_redir *redir, t_shell *shell)
{
	int	fd;

	while (redir)
	{
		fd = open_redirection(redir);
		if (fd < 0)
		{
			perror(redir->filename);
			shell->exit_status = 1;
			return (0);
		}
		if (redir->type == T_REDIR_IN || redir->type == T_HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
	return (1);
}
