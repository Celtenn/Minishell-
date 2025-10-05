/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:42:24 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:40:31 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/executer.h"
#include <sys/wait.h>
#include <unistd.h>
#include <readline/readline.h>

static int	check_all_heredocs(t_list *cmds, t_shell *shell)
{
	t_list	*tmp;
	t_cmd	*cmd;

	tmp = cmds;
	while (tmp)
	{
		cmd = (t_cmd *)tmp->content;
		if (prepare_heredocs(cmd, shell) < 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

static pid_t	fork_pipeline(t_list *cmds, t_shell *shell)
{
	int		pipefd[2];
	int		prev_read;
	pid_t	pid;
	t_cmd	*cmd;

	prev_read = -1;
	pid = -1;
	setup_signals_execution();
	while (cmds)
	{
		cmd = (t_cmd *)cmds->content;
		if (cmd->pipe_next)
			if (pipe(pipefd) == -1)
				perror("minishell: pipe");
		pid = fork();
		if (pid == -1)
			perror("minishell: fork");
		else if (pid == 0)
			handle_child_process(cmd, prev_read, pipefd, shell);
		else
			handle_parent_process(&prev_read, cmd, pipefd);
		cmds = cmds->next;
	}
	return (pid);
}

static void	handle_exit_status(int status, t_shell *shell, int *is_signaled)
{
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			*is_signaled = 1;
		else if (WTERMSIG(status) == SIGQUIT)
		{
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
			*is_signaled = 1;
		}
	}
}

static void	wait_for_pipeline(pid_t last_pid, t_shell *shell)
{
	int		status;
	pid_t	waited_pid;
	int		is_signaled;

	is_signaled = 0;
	while (1)
	{
		waited_pid = wait(&status);
		if (waited_pid <= 0)
			break ;
		if (waited_pid == last_pid)
			handle_exit_status(status, shell, &is_signaled);
	}
	setup_signals_interactive();
	if (is_signaled)
		write(STDOUT_FILENO, "\n", 1);
}

void	execute_commands(t_list *cmds, t_shell *shell)
{
	t_cmd	*first_cmd;

	if (!cmds || !check_all_heredocs(cmds, shell))
		return ;
	first_cmd = (t_cmd *)cmds->content;
	if (is_builtin(first_cmd->argv[0]) && !first_cmd->pipe_next)
	{
		handle_single_builtin(first_cmd, shell);
		return ;
	}
	wait_for_pipeline(fork_pipeline(cmds, shell), shell);
}
