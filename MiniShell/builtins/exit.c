/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:05:45 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:40:53 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
#include <readline/history.h>
#include <unistd.h>
#include <readline/readline.h>

void	clean_exit(t_shell *shell, int exit_code)
{
	if (shell)
	{
		rl_clear_history();
		free_shell(shell);
		free_env_header(shell->env);
		gc_destroy(shell->gc, 1);
	}
	exit(exit_code);
}

static void	builtin_clear(char **argv, t_shell *shell)
{
	write(2, "minishell; exit; ", 17);
	write(2, argv[1], ft_strlen(argv[1]));
	write(2, "; numeric argument required\n", 28);
	clean_exit(shell, 2);
}

static int	is_numeric_argument(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (str[i] == '\0');
}

int	builtin_exit(char **argv, t_shell *shell)
{
	if (argv[1] && !is_numeric_argument(argv[1]))
		builtin_clear(argv, shell);
	if (argv[1] && argv[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		shell->exit_status = 1;
		return (1);
	}
	printf("exit\n");
	if (!argv[1])
		clean_exit(shell, shell->exit_status);
	else if (!is_numeric_argument(argv[1]))
		builtin_clear(argv, shell);
	else
		clean_exit(shell, ft_exitatoi(argv[1]) & 255);
	return (0);
}
