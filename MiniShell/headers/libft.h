/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:01:50 by omadali           #+#    #+#             */
/*   Updated: 2025/07/14 20:01:50 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include<stdlib.h>

char	*ft_strdup(const char *s1);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_realloc(void *ptr, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_isdigit(int a);
int		ft_isalnum(int c);
int		ft_isspace(char c);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strchr(const char *s, int c);
char	*ft_strtok(char *str, const char *delim);
int		ft_exitatoi(const char *str);
char	*ft_itoa(int n);
int		ft_strcpy(char *dst, const char *src);
char	**ft_split(char const *s, char c);
void	free_str_array(char **str_array);
void	*ft_memmove(void *dest, const void *src, size_t n);

#endif