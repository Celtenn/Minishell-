/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:19:38 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/parser.h"
#include "../headers/executer.h"
#include <unistd.h>
#include <readline/readline.h>

void	safe_exit(t_shell *shell, int exit_code)
{
	rl_clear_history();
	free_env_header(shell->env);
	gc_destroy(shell->gc, 1);
	close(shell->stdin_backup);
	close(shell->stdout_backup);
	exit(exit_code);
}

void	exec_command(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (!cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		safe_exit(shell, 0);
	if (!apply_redirections(cmd->redirs, shell))
		safe_exit(shell, 1);
	path = find_executable(cmd->argv[0], shell);
	if (!path)
	{
		write(2, "Command not found: ", 19);
		write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(2, "\n", 1);
		safe_exit(shell, 127);
	}
	execve(path, cmd->argv, shell->env);
	perror("execve failed");
	safe_exit(shell, 126);
}

void	handle_single_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!apply_redirections(cmd->redirs, shell))
		return ;
	exec_builtin(cmd->argv, shell);
}

void	handle_child_process(t_cmd *cmd, int prev_read, int *pipefd,
							t_shell *shell)
{
	if (prev_read != -1)
	{
		dup2(prev_read, STDIN_FILENO);
		close(prev_read);
	}
	if (cmd->pipe_next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	if (!apply_redirections(cmd->redirs, shell))
		safe_exit(shell, 1);
	restore_signals_default();
	if (is_builtin(cmd->argv[0]))
		exec_builtin(cmd->argv, shell);
	else
		exec_command(cmd, shell);
	safe_exit(shell, 1);
}

void	handle_parent_process(int *prev_read, t_cmd *cmd, int pipefd[2])
{
	if (*prev_read != -1)
		close(*prev_read);
	if (cmd->pipe_next)
	{
		close(pipefd[1]);
		*prev_read = pipefd[0];
	}
}
