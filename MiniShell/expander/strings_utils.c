/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:31:07 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_single_var_reference(const char *input)
{
	int	i;

	i = 1;
	if (!input || input[0] != '$')
		return (0);
	while (ft_isalnum(input[i]) || input[i] == '_')
		i++;
	return (input[i] == '\0');
}

char	*append_to_result(t_gc *gc, char *result, const char *append)
{
	char	*new_result;

	new_result = gc_realloc(gc, result, ft_strlen(result)
			+ ft_strlen(append) + 1);
	if (new_result)
		ft_strcat(new_result, append);
	return (new_result);
}

char	*append_char_to_result(t_gc *gc, char *result, char c)
{
	char	temp[2];

	temp[0] = c;
	temp[1] = '\0';
	return (append_to_result(gc, result, temp));
}
