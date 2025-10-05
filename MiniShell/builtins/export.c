/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:05:45 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:32:50 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/builtins.h"
#include <unistd.h>

char	*remove_outer_quotes(const char *s)
{
	char	*equal_pos;
	char	*key;
	char	*value;

	equal_pos = ft_strchr(s, '=');
	if (!equal_pos)
		return (ft_strdup(s));
	key = ft_strndup(s, equal_pos - s);
	if (!key)
		return (NULL);
	value = ft_strdup(equal_pos + 1);
	if (!value)
	{
		free(key);
		return (NULL);
	}
	return (rebuild_string(key, value));
}

static int	handle_export_with_equal(char *arg, char *name, t_shell *shell)
{
	char	*cleaned;

	env_var_remove(&shell->env, name);
	cleaned = remove_outer_quotes(arg);
	if (!env_add_var(&shell->env, cleaned))
	{
		free(cleaned);
		return (1);
	}
	free(cleaned);
	return (0);
}

static int	handle_export_without_equal(char *name, t_shell *shell)
{
	if (!export_checker(name))
	{
		write(2, "minishell: export: `", 20);
		write(2, name, ft_strlen(name));
		write(2, "`: not a valid identifier\n", 26);
		return (1);
	}
	if (!env_var_exists(shell->env, name))
	{
		if (!env_add_var(&shell->env, name))
			return (1);
	}
	return (0);
}

int	process_export_arg(char *arg, t_shell *shell)
{
	char	*equal;
	char	*name;
	int		ret;

	if (arg && (ft_isdigit(arg[0]) || arg[0] == '='))
	{
		write(2, "minishell: export: `", 20);
		write(2, arg, ft_strlen(arg));
		write(2, "`: not a valid identifier\n", 26);
		return (1);
	}
	equal = ft_strchr(arg, '=');
	if (equal)
		name = ft_strndup(arg, equal - arg);
	else
		name = ft_strdup(arg);
	if (!name)
		return (1);
	if (equal)
		ret = handle_export_with_equal(arg, name, shell);
	else
		ret = handle_export_without_equal(name, shell);
	free(name);
	return (ret);
}

int	builtin_export(char **argv, t_shell *shell)
{
	int	i;
	int	ret;

	if (!argv[1])
	{
		print_sorted_env(shell->env);
		shell->exit_status = 0;
		return (0);
	}
	i = 1;
	ret = 0;
	while (argv[i])
	{
		ret |= process_export_arg(argv[i], shell);
		if (ret)
		{
			shell->exit_status = 1;
			return (ret);
		}
		i++;
	}
	shell->exit_status = 0;
	return (ret);
}
