/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:05:45 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:23:18 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/builtins.h"
#include <unistd.h>
#include <errno.h>
#include <readline/readline.h>

static void	update_pwd_vars(char *oldpwd, t_shell *shell)
{
	char	cwd[4096];
	char	*line;

	if (getcwd(cwd, sizeof(cwd)))
	{
		line = gc_malloc(shell->gc, ft_strlen("OLDPWD=")
				+ ft_strlen(oldpwd) + 1);
		if (line)
		{
			ft_strcpy(line, "OLDPWD=");
			ft_strcat(line, oldpwd);
			update_env_var(line, shell);
		}
		line = gc_malloc(shell->gc, ft_strlen("PWD=") + ft_strlen(cwd) + 1);
		if (line)
		{
			ft_strcpy(line, "PWD=");
			ft_strcat(line, cwd);
			update_env_var(line, shell);
		}
	}
	else
		perror("minishell: cd: getcwd");
}

static char	*get_cd_target(char **argv, t_shell *shell)
{
	char	*target;

	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
		target = get_var_value("HOME", shell);
	else if (ft_strcmp(argv[1], "-") == 0)
	{
		target = get_var_value("OLDPWD", shell);
		if (!target || !*target)
		{
			write(2, "minishell: cd: OLDPWD not set\n", 31);
			return (NULL);
		}
		printf("%s\n", target);
	}
	else
		target = ft_strdup(argv[1]);
	return (target);
}

static int	perform_cd_and_update(char *target, char *oldpwd, t_shell *shell)
{
	if (chdir(target) != 0)
	{
		write(2, "minishell: cd: ", 15);
		write(2, target, ft_strlen(target));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		free(target);
		free(oldpwd);
		shell->exit_status = 1;
		return (1);
	}
	update_pwd_vars(oldpwd, shell);
	free(target);
	free(oldpwd);
	return (0);
}

int	cd_error(char *argv, t_shell *shell)
{
	if (argv)
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		shell->exit_status = 1;
		return (1);
	}
	return (0);
}

int	builtin_cd(char **argv, t_shell *shell)
{
	char	*target;
	char	*oldpwd_val;
	char	temp_pwd[4096];

	if (cd_error(argv[2], shell))
		return (1);
	oldpwd_val = get_var_value("PWD", shell);
	if (!oldpwd_val)
	{
		if (getcwd(temp_pwd, sizeof(temp_pwd)) == NULL)
		{
			perror("minishell: cd: getcwd");
			return (1);
		}
		oldpwd_val = ft_strdup(temp_pwd);
	}
	target = get_cd_target(argv, shell);
	if (!target)
	{
		free(oldpwd_val);
		return (1);
	}
	return (perform_cd_and_update(target, oldpwd_val, shell));
}
