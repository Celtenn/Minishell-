/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:01:02 by omadali           #+#    #+#             */
/*   Updated: 2025/07/14 19:53:00 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	find_and_remove_var(const char *name, int len, t_shell *shell)
{
	int	i;
	int	k;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& shell->env[i][len] == '=')
		{
			free(shell->env[i]);
			k = i;
			while (shell->env[k])
			{
				shell->env[k] = shell->env[k + 1];
				k++;
			}
			return ;
		}
		i++;
	}
}

static void	add_new_var(const char *entry, t_shell *shell)
{
	int		count;
	char	**new_env;

	count = 0;
	while (shell->env[count])
		count++;
	new_env = ft_realloc(shell->env, sizeof(char *) * (count + 2));
	if (!new_env)
		return ;
	shell->env = new_env;
	shell->env[count] = ft_strdup(entry);
	shell->env[count + 1] = NULL;
}

void	update_env_var(const char *entry, t_shell *shell)
{
	char	*equal;
	char	*name;
	int		name_len;

	equal = ft_strchr(entry, '=');
	if (!equal)
		return ;
	name_len = equal - entry;
	name = ft_strndup(entry, name_len);
	if (!name)
		return ;
	find_and_remove_var(name, name_len, shell);
	add_new_var(entry, shell);
	free(name);
}
