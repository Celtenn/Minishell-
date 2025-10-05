/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:05:45 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:21:37 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <unistd.h>
#include <stdio.h>

int	builtin_pwd(char **argv, t_shell *shell)
{
	char	cwd[4096];

	(void)argv;
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd");
	shell->exit_status = 0;
	return (0);
}
