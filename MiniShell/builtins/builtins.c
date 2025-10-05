/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:05:45 by omadali           #+#    #+#             */
/*   Updated: 2025/08/01 18:52:36 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	return (0);
}

int	exec_builtin(char **argv, t_shell *shell)
{
	if (!argv || !argv[0])
		return (1);
	if (ft_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(argv, shell));
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argv, shell));
	else if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argv, shell));
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd(argv, shell));
	else if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env(argv, shell->env, shell));
	else if (ft_strcmp(argv[0], "export") == 0)
		return (builtin_export(argv, shell));
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (builtin_unset(argv, shell));
	return (1);
}
