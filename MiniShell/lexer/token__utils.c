/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token__utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 13:15:00 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:28:40 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	is_special(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token	*add_token(t_tokenizer_state *haha, const char *val,
		t_token_type type, t_gc *gc)
{
	t_token	*new;
	t_token	*tmp;
	t_token	**head;

	head = haha->tokens;
	new = gc_malloc(gc, sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = gc_strdup(gc, val);
	new->type = type;
	new->in_herodocc = *haha->in_heredoc;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

void	skip_spaces(char *input, int *i)
{
	while (input[*i] && ft_isspace((unsigned char)input[*i]))
		(*i)++;
}
