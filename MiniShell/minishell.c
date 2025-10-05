/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:42:54 by omadali           #+#    #+#             */
/*   Updated: 2025/07/04 16:42:54 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"
#include "headers/parser.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

static int	initialize_shell(t_shell *shell, int argc, char **envp)
{
	if (argc != 1)
	{
		write(2, "please do not enter arguments\n", 30);
		exit(0);
	}
	shell->gc = gc_init();
	if (!shell->gc)
	{
		write(2, "Memory allocation failed\n", 25);
		return (0);
	}
	get_set_gc(shell->gc);
	setup_signals_interactive();
	shell->exit_status = 0;
	if (!(init_shell(shell, envp)))
	{
		write(2, "Failed to initialize shell\n", 28);
		gc_destroy(shell->gc, 0);
		return (0);
	}
	return (1);
}

static int	is_allspace(char *str)
{
	while (*str)
	{
		if (!ft_isspace((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}

static char	*make_fd(t_shell *shell, char *input)
{
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
	gc_malloc_fd(shell->gc, shell->stdin_backup);
	gc_malloc_fd(shell->gc, shell->stdout_backup);
	return (gc_strdup(shell->gc, input));
}

static void	process_input_loop(t_shell *shell)
{
	char	*input;
	char	*gc_input;

	while (1)
	{
		shell->syntax_error = 0;
		input = readline("💀 \033[1;31mLa muerte\033[0m es \033[1;34mabsoluta\033[0m ☠️ ➤ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input && !is_allspace(input))
		{
			add_history(input);
			gc_input = make_fd(shell, input);
			if (!parse_input(gc_input, shell))
				write(2, "Parse error!\n", 13);
			else
				execute_commands(shell->cmds, shell);
		}
		free(input);
		free_shell(shell);
		gc_free_all(shell->gc, 1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	shell.exit_status = 0;
	(void)argv;
	if (!initialize_shell(&shell, argc, envp))
		return (1);
	process_input_loop(&shell);
	close(shell.stdin_backup);
	close(shell.stdout_backup);
	free_env_header(shell.env);
	gc_destroy(shell.gc, 0);
	shell.gc = NULL;
	return (0);
}

