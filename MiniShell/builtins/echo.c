/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:05:45 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:41:02 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <readline/readline.h>

static int	is_nonewline(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] != '-')
		return (1);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	builtin_echo(char **argv, t_shell *shell)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (argv[i] && is_nonewline(argv[i]) == 0)
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	shell->exit_status = 0;
	return (0);
}
