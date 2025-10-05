/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:05:45 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:23:57 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/builtins.h"
#include <unistd.h>
#include <stdio.h>

int	builtin_env(char **argv, char **env, t_shell *shell)
{
	int	i;

	i = 0;
	if (argv[1])
	{
		write(2, "env : no arguments\n", 19);
		shell->exit_status = 127;
		return (1);
	}
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	shell->exit_status = 0;
	return (0);
}

static void	allocate_sorted_env(char **sorted, char **env, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		sorted[i] = ft_strdup(env[i]);
		i++;
	}
	sorted[count] = NULL;
}

static void	sort_env_array(char **sorted, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(sorted[j], sorted[j + 1]) > 0)
			{
				tmp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_env_entries(char **sorted, int count)
{
	int		i;
	char	*eq;

	i = 0;
	while (i < count)
	{
		eq = ft_strchr(sorted[i], '=');
		if (eq)
		{
			*eq = '\0';
			printf("declare -x %s=\"%s\"\n", sorted[i], eq + 1);
			*eq = '=';
		}
		else
			printf("declare -x %s\n", sorted[i]);
		free(sorted[i]);
		i++;
	}
}

void	print_sorted_env(char **env)
{
	int		count;
	char	**sorted;

	count = 0;
	while (env[count])
		count++;
	sorted = malloc(sizeof(char *) * (count + 1));
	if (!sorted)
		return ;
	allocate_sorted_env(sorted, env, count);
	sort_env_array(sorted, count);
	print_env_entries(sorted, count);
	free(sorted);
}
