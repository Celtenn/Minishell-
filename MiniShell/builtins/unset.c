/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:05:45 by omadali           #+#    #+#             */
/*   Updated: 2025/08/07 02:16:56 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	remove_env_var(char **env, const char *name)
{
	int	j;
	int	k;

	j = 0;
	while (env[j])
	{
		if (ft_strncmp(env[j], name, ft_strlen(name)) == 0
			&& env[j][ft_strlen(name)] == '=')
		{
			free(env[j]);
			k = j;
			while (env[k])
			{
				env[k] = env[k + 1];
				k++;
			}
			return ;
		}
		j++;
	}
}

int	builtin_unset(char **argv, t_shell *shell)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		remove_env_var(shell->env, argv[i]);
		i++;
	}
	shell->exit_status = 0;
	return (0);
}
