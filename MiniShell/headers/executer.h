/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idkahram <idkahram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/08/01 16:57:27 by idkahram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"
# include "parser.h"

char	*find_executable(char *cmd, t_shell *shell);

int		create_heredoc_pipe(const char *delimiter, t_shell *shell, int quoted);
int		prepare_heredocs(t_cmd *cmd, t_shell *shell);

int		apply_redirections(t_redir *redir, t_shell *shell);

void	handle_single_builtin(t_cmd *cmd, t_shell *shell);
void	handle_child_process(t_cmd *cmd, int prev_read, int *pipefd,
			t_shell *shell);

void	handle_parent_process(int *prev_read, t_cmd *cmd, int pipefd[2]);

void	exec_command(t_cmd *cmd, t_shell *shell);
void	safe_exit(t_shell *shell, int exit_code);

#endif