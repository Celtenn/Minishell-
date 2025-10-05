/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:43:00 by omadali           #+#    #+#             */
/*   Updated: 2025/07/04 16:43:00 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parser.h"
#include <unistd.h>

char	**get_set_env(char **new_env)
{
	static char	**env = NULL;

	if (new_env != NULL)
		env = new_env;
	return (env);
}

int	init_shell(t_shell *shell, char **envp)
{
	int	count;
	int	i;

	count = 0;
	while (envp[count])
		count++;
	shell->env = malloc(sizeof(char *) * (count + 1));
	if (!shell->env)
		return (0);
	i = 0;
	while (i < count)
	{
		shell->env[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->env[count] = NULL;
	shell->cmds = NULL;
	get_set_env(shell->env);
	return (1);
}

void	free_shell(t_shell *shell)
{
	if (shell->cmds)
		clear_cmd_list(shell->cmds);
	shell->cmds = NULL;
	dup2(shell->stdin_backup, STDIN_FILENO);
	dup2(shell->stdout_backup, STDOUT_FILENO);
}

void	free_env_header(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	*gc_realloc(t_gc *gc, char *old, size_t new_size)
{
	char	*new_mem;

	new_mem = gc_malloc(gc, new_size);
	if (!new_mem)
		return (NULL);
	ft_memcpy(new_mem, old, ft_strlen(old) + 1);
	return (new_mem);
}
