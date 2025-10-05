/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:18:27 by omadali           #+#    #+#             */
/*   Updated: 2025/08/03 14:39:27 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include "../headers/builtins.h"

char	*rebuild_string(char *key, char *value)
{
	char	*final;
	size_t	total_len;

	strip_outer_quotes(value);
	total_len = ft_strlen(key) + ft_strlen(value) + 2;
	final = malloc(sizeof(char) * total_len);
	if (!final)
	{
		free(key);
		free(value);
		return (NULL);
	}
	ft_strcpy(final, key);
	ft_strcat(final, "=");
	ft_strcat(final, value);
	free(key);
	free(value);
	return (final);
}

int	export_checker(char *arg)
{
	int	a;

	a = 0;
	if (!arg || !*arg)
		return (0);
	while (arg[a])
	{
		if (!ft_isalnum(arg[a]) && arg[a] != '_')
			return (0);
		a++;
	}
	return (1);
}
