/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_finder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:40:40 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <unistd.h>
#include <readline/readline.h>

static char	*try_path_locations(char *cmd, char *path, t_shell *shell)
{
	char	*paths;
	char	*token;
	char	*full;

	paths = gc_strdup(shell->gc, path);
	free(path);
	token = ft_strtok(paths, ":");
	while (token)
	{
		full = gc_malloc(shell->gc, ft_strlen(token) + ft_strlen(cmd) + 2);
		if (!full)
			return (NULL);
		ft_strcpy(full, token);
		ft_strcat(full, "/");
		ft_strcat(full, cmd);
		if (access(full, X_OK) == 0)
			return (full);
		token = ft_strtok(NULL, ":");
	}
	return (NULL);
}

char	*find_executable(char *cmd, t_shell *shell)
{
	char	*path;

	if (strchr(cmd, '/'))
		return (gc_strdup(shell->gc, cmd));
	path = get_var_value("PATH", shell);
	if (!path || !*path)
	{
		free(path);
		return (NULL);
	}
	return (try_path_locations(cmd, path, shell));
}
