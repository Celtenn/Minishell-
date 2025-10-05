/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftfc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:42:42 by omadali           #+#    #+#             */
/*   Updated: 2025/07/04 16:42:42 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last;
	char		*token_start;

	if (str)
		last = str;
	if (!last)
		return (NULL);
	while (*last && ft_strchr(delim, *last))
		last++;
	if (*last == '\0')
	{
		last = NULL;
		return (NULL);
	}
	token_start = last;
	while (*last && !ft_strchr(delim, *last))
		last++;
	if (*last)
	{
		*last = '\0';
		last++;
	}
	else
		last = NULL;
	return (token_start);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*res;

	i = 0;
	res = malloc(n + 1);
	if (!res)
		return (NULL);
	while (i < n && s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if ((unsigned char)c == 0)
		return ((char *)s + i);
	return (0);
}

void	free_str_array(char **str_array)
{
	int	i;

	i = 0;
	if (!str_array)
		return ;
	while (str_array[i])
	{
		free(str_array[i]);
		i++;
	}
	free(str_array);
}
