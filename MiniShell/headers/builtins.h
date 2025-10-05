/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:05:45 by omadali           #+#    #+#             */
/*   Updated: 2025/08/03 14:39:09 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		is_builtin(char *cmd);
int		exec_builtin(char **argv, t_shell *shell);

int		builtin_cd(char **argv, t_shell *shell);
void	update_env_var(const char *entry, t_shell *shell);

int		builtin_echo(char **argv, t_shell *shell);

int		builtin_env(char **argv, char **env, t_shell *shell);
void	print_sorted_env(char **env);

int		env_var_exists(char **env, const char *name);
void	env_var_remove(char ***env, const char *name);
int		env_add_var(char ***env, const char *entry);
void	strip_outer_quotes(char *value);

char	*rebuild_string(char *key, char *value);

int		builtin_exit(char **argv, t_shell *shell);
int		is_allspace(char *str);

int		builtin_export(char **argv, t_shell *shell);
int		env_add_var(char ***env, const char *entry);
char	*remove_quotes(const char *s);
void	print_sorted_env(char **env);

int		builtin_pwd(char **argv, t_shell *shell);

int		builtin_unset(char **argv, t_shell *shell);
void	clean_exit(t_shell *shell, int exit_code);
int		export_checker(char *arg);

#endif