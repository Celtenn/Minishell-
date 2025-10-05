/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:40:25 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/executer.h"
#include <sys/wait.h>
#include <unistd.h>
#include <readline/readline.h>

static void	heredoc_read_lines(int pipefd, const char *delim, t_shell *shell,
								int quoted)
{
	char	*line;
	char	*expanded;

	signal(SIGINT, heredoc_sigint_handler);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		if (quoted)
		{
			write(pipefd, line, ft_strlen(line));
			write(pipefd, "\n", 1);
		}
		else
		{
			expanded = expand_variables(line, shell, 1);
			write(pipefd, expanded, ft_strlen(expanded));
			write(pipefd, "\n", 1);
		}
		free(line);
	}
}

static int	handle_heredoc_parent(int pipefd[2], pid_t pid, t_shell *shell)
{
	int	status;

	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipefd[0]);
		shell->exit_status = 130;
		return (-1);
	}
	return (pipefd[0]);
}

int	create_heredoc_pipe(const char *delimiter, t_shell *shell, int quoted)
{
	int		fd;
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) < 0)
		return (-1);
	setup_signals_execution();
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(pipefd[0]);
		gc_malloc_fd(shell->gc, pipefd[1]);
		heredoc_read_lines(pipefd[1], delimiter, shell, quoted);
		if (pipefd[1] != -1)
			close(pipefd[1]);
		safe_exit(shell, 0);
	}
	fd = handle_heredoc_parent(pipefd, pid, shell);
	setup_signals_interactive();
	return (fd);
}

int	prepare_heredocs(t_cmd *cmd, t_shell *shell)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == T_HEREDOC)
		{
			r->heredoc_fd = create_heredoc_pipe(r->filename, shell,
					r->quoted_delim);
			if (r->heredoc_fd < 0)
				return (-1);
		}
		r = r->next;
	}
	return (0);
}
