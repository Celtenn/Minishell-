/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:34:20 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parser.h"

t_list	*ft_lstnew_gc(void *content, t_gc *gc)
{
	t_list	*node;

	node = gc_malloc(gc, sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	is_all_spaces(const char *s)
{
	while (*s)
	{
		if (!(*s == ' ' || *s == '\t' || *s == '\n'
				|| *s == '\v' || *s == '\f' || *s == '\r'))
			return (0);
		s++;
	}
	return (1);
}

int	count_args(t_token *start)
{
	int		count;
	t_token	*curr;

	count = 0;
	curr = start;
	while (curr && curr->type != T_PIPE)
	{
		if (curr->type == T_WORD)
		{
			count++;
			curr = curr->next;
		}
		else if (curr->type == T_REDIR_IN || curr->type == T_REDIR_OUT
			|| curr->type == T_APPEND || curr->type == T_HEREDOC)
		{
			curr = curr->next;
			if (curr)
				curr = curr->next;
		}
		else
			curr = curr->next;
	}
	return (count);
}
