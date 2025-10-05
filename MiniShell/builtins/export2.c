/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:13:35 by omadali           #+#    #+#             */
/*   Updated: 2025/08/07 02:16:49 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/builtins.h"

int	env_var_exists(char **env, const char *name)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (env[i])
	{
		if ((ft_strncmp(env[i], name, name_len) == 0
				&& env[i][name_len] == '=') || (ft_strcmp(env[i], name) == 0))
			return (1);
		i++;
	}
	return (0);
}

void	env_var_remove(char ***env, const char *name)
{
	int	i;
	int	j;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], name, name_len) == 0
			&& (*env)[i][name_len] == '=')
		{
			free((*env)[i]);
			j = i;
			while ((*env)[j])
			{
				(*env)[j] = (*env)[j + 1];
				j++;
			}
			return ;
		}
		i++;
	}
}

static int	env_copy_and_add(char ***env, const char *entry, int count)
{
	char	**new_tab;

	new_tab = malloc((count + 2) * sizeof(char *));
	if (!new_tab)
		return (0);
	ft_memcpy(new_tab, *env, count * sizeof(char *));
	new_tab[count] = ft_strdup(entry);
	if (!new_tab[count])
	{
		free(new_tab);
		return (0);
	}
	new_tab[count + 1] = NULL;
	free(*env);
	*env = new_tab;
	return (1);
}

int	env_add_var(char ***env, const char *entry)
{
	int	count;

	if (!env || !*env || !entry)
		return (0);
	count = 0;
	while ((*env)[count])
		count++;
	return (env_copy_and_add(env, entry, count));
}

void	strip_outer_quotes(char *value)
{
	size_t	len;

	if (!value)
		return ;
	len = ft_strlen(value);
	if (len < 2)
		return ;
	if ((value[0] == '"' && value[len - 1] == '"')
		|| (value[0] == '\'' && value[len - 1] == '\''))
	{
		value[len - 1] = '\0';
		ft_memmove(value, value + 1, len);
	}
}
