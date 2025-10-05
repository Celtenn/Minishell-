/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lookup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:30:40 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/expander.h"

static char	*search_env_var(const char *name, t_shell *shell)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, name_len) == 0
			&& shell->env[i][name_len] == '=')
			return (ft_strdup(shell->env[i] + name_len + 1));
		i++;
	}
	return (NULL);
}

char	*get_var_value(const char *name, t_shell *shell)
{
	if (!name || !shell || !shell->env)
		return (NULL);
	return (search_env_var(name, shell));
}

char	*expand_exit_status(t_gc *gc, char *result, int *i)
{
	char	*value;
	char	*new_result;

	(*i)++;
	value = get_var_value("?", NULL);
	if (!value)
		value = ft_strdup("");
	new_result = append_to_result(gc, result, value);
	free(value);
	return (new_result);
}

char	*expand_env_var(const char *input, int *i, t_shell *shell, char *result)
{
	int		start;
	char	*varname;
	char	*value;
	char	*new_result;

	start = *i;
	while (ft_isalnum((unsigned char)input[*i]) || input[*i] == '_')
		(*i)++;
	varname = ft_strndup(&input[start], *i - start);
	if (!varname)
		return (result);
	value = get_var_value(varname, shell);
	free(varname);
	if (!value)
		return (NULL);
	new_result = append_to_result(shell->gc, result, value);
	free(value);
	return (new_result);
}
