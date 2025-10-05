/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftfc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:42:16 by omadali           #+#    #+#             */
/*   Updated: 2025/07/04 16:42:16 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	k;
	char	*yey;

	i = 0;
	k = 0;
	while (s1[i] != '\0')
	{
		i++;
	}
	yey = malloc(i + 1);
	if (yey == 0)
		return (0);
	while (k < i)
	{
		yey[k] = s1[k];
		k++;
	}
	yey[k] = '\0';
	return (yey);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*b;

	i = 0;
	b = (char *)malloc(count * size);
	if (b == 0)
		return (0);
	while (i < (count * size))
	{
		b[i] = '\0';
		i++;
	}
	return ((void *)b);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && (i < n))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}
