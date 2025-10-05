/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:42:47 by omadali           #+#    #+#             */
/*   Updated: 2025/07/04 16:42:47 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parser.h"
#include "../headers/lexer.h"

t_list	*build_command_list(t_token *tokens, t_shell *shell)
{
	t_list	*cmd_list;
	t_token	*cur;
	t_cmd	*cmd;

	cmd_list = NULL;
	cur = tokens;
	while (cur)
	{
		cmd = parse_single_command(&cur, shell);
		if (!cmd)
		{
			shell->exit_status = 2;
			clear_cmd_list(cmd_list);
			return (NULL);
		}
		ft_lstadd_back(&cmd_list, ft_lstnew_gc(cmd, shell->gc));
	}
	return (cmd_list);
}

int	check_minishell(t_token *input, t_token *check)
{
	int	flag;

	flag = 0;
	while (check)
	{
		if (!ft_strcmp((const char *)input->value, "./minishell"))
			flag = 1;
		if (flag)
			return (0);
		input = input->next;
		check = check->next;
	}
	return (1);
}

int	parse_input(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_token	*current;
	t_token	*currentnext;

	tokens = tokenize(input, shell);
	if (!tokens)
		return (0);
	current = tokens;
	currentnext = tokens->next;
	if (!check_minishell(current, currentnext))
		return (0);
	shell->cmds = build_command_list(tokens, shell);
	return (shell->cmds != NULL);
}
