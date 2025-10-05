/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftfc4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:42:44 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:11:40 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

int	jaja(const char *hel, int *k)
{
	int	negative;
	int	i;

	i = 0;
	negative = 1;
	while ((hel[i] >= 9 && hel[i] <= 13) || hel[i] == 32)
	{
		i += 1;
	}
	if (hel[i] == 45)
	{
		negative *= -1;
		i += 1;
	}
	else if (hel[i] == 43)
		i += 1;
	*k = i;
	return (negative);
}

int	ft_exitatoi(const char *str)
{
	int	i;
	int	neg;
	int	result;

	i = 0;
	result = 0;
	neg = jaja(str, &i);
	while (str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i])
		return (0);
	result *= neg;
	return (result);
}

static int	count_word(long int a, int *result)
{
	int	b;

	b = 0;
	if (a < 0)
	{
		a = a * -1;
		b++;
		*result = 1;
	}
	if (a == 0)
		b++;
	while (a > 0)
	{
		a = a / 10;
		b++;
	}
	return (b);
}

char	*ft_itoa(int n)
{
	long int	a;
	int			b;
	char		*c;
	int			result;

	result = 0;
	a = n;
	b = count_word(a, &result);
	c = (char *)malloc(sizeof(char) * (b + 1));
	if (!c)
		return (NULL);
	if (result == 1)
	{
		c[0] = '-';
		a *= -1;
	}
	c[b--] = 0;
	while (a > 0)
	{
		c[b--] = 48 + (a % 10);
		a /= 10;
	}
	if (n == 0)
		c[0] = 48;
	return (c);
}

int	ft_strcpy(char *dst, const char *src)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	i = 0;
	while (src[i] != '\0' && i < src_len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
