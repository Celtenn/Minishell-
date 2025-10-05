/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:01:54 by omadali           #+#    #+#             */
/*   Updated: 2025/07/14 20:01:54 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "gc.h"
# include "structs.h"

typedef struct s_shell
{
	char	**env;
	char	*exported_env;
	t_list	*cmds;
	int		stdin_backup;
	int		stdout_backup;
	t_gc	*gc;
	int		quoted;
	int		exit_status;
	int		syntax_error;
	t_token	**tokens;
}	t_shell;

int		init_shell(t_shell *shell, char **envp);
void	free_shell(t_shell *shell);
void	free_env_header(char **env);
void	execute_commands(t_list *cmds, t_shell *shell);
char	*expand_variables(const char *input, t_shell *shell, int flag);

int		builtin_cd(char **argv, t_shell *shell);
int		builtin_exit(char **argv, t_shell *shell);
int		builtin_echo(char **argv, t_shell *shell);
int		is_builtin(char *cmd);
int		exec_builtin(char **argv, t_shell *shell);

int		builtin_pwd(char **argv, t_shell *shell);
int		builtin_env(char **argv, char **env, t_shell *shell);
int		builtin_export(char **argv, t_shell *shell);
int		builtin_unset(char **argv, t_shell *shell);

char	*get_var_value(const char *name, t_shell *shell);

void	setup_signals_execution(void);
void	setup_signals_interactive(void);
char	*gc_realloc(t_gc *gc, char *old, size_t new_size);
void	restore_signals_default(void);
void	heredoc_sigint_handler(int sig);
char	**get_set_env(char **new_env);

#endif