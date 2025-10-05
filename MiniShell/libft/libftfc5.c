/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftfc5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 02:49:10 by omadali           #+#    #+#             */
/*   Updated: 2025/07/29 02:49:10 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	countw(char const *s, char c)
{
	int	i;
	int	wnumber;

	i = 0;
	wnumber = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			i++;
		}
		else
		{
			wnumber++;
			while (s[i] != c && s[i])
			{
				i++;
			}
		}
	}
	return (wnumber);
}

char	*creatw(char *daz, char const *s, int first_i, int last_i)
{
	int	i;

	i = 0;
	while (i < last_i)
	{
		daz[i] = s[first_i + i];
		i++;
	}
	daz[i] = '\0';
	return (daz);
}

char	*create_single_word(char const *s, int *index, char c)
{
	int		w_len;
	int		first;
	char	*word;

	w_len = 0;
	first = *index;
	while (s[*index] != c && s[*index])
	{
		w_len++;
		(*index)++;
	}
	word = (char *)malloc(sizeof(char) * (w_len + 1));
	if (!word)
		return (0);
	creatw(word, s, first, w_len);
	return (word);
}

char	**create_word(char **daza, char const *s, char c, int k_len)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s[i] && k < k_len)
	{
		if (s[i] != c)
		{
			daza[k] = create_single_word(s, &i, c);
			if (!daza[k])
			{
				while (--k > -1)
					free(daza[k]);
				free(daza);
				return (0);
			}
			k++;
		}
		else
			i++;
	}
	daza[k] = NULL;
	return (daza);
}

char	**ft_split(char const *s, char c)
{
	int		k_len;
	char	**str;

	if (!s)
		return (0);
	k_len = countw(s, c);
	str = (char **)malloc(sizeof(char *) * (k_len + 1));
	if (!str)
		return (0);
	str = create_word(str, s, c, k_len);
	return (str);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	char		*s;

	if (!dest && !src)
		return (0);
	d = (char *)dest;
	s = (char *)src;
	if (d - s > 0)
	{
		d += n - 1;
		s += n - 1;
		while (n-- > 0)
			*d-- = *s--;
	}
	else
	{
		while (n-- > 0)
			*d++ = *s++;
	}
	return (dest);
}