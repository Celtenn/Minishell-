/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:42:50 by omadali           #+#    #+#             */
/*   Updated: 2025/07/04 16:42:50 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/gc.h"
#include <unistd.h>

t_gc	*gc_init(void)
{
	t_gc	*gc;

	gc = malloc(sizeof(t_gc));
	if (gc)
		gc->allocations = NULL;
	return (gc);
}

t_gc	*get_set_gc(t_gc *new_gc)
{
	static t_gc	*static_gc = NULL;

	if (new_gc != NULL)
		static_gc = new_gc;
	return (static_gc);
}

void	gc_destroy(t_gc *gc, int flag)
{
	if (!gc)
		return ;
	gc_free_all(gc, flag);
	free(gc);
}

void	gc_free_all(t_gc *gc, int flag)
{
	t_gc_node	*tmp;

	if (!gc)
		return ;
	while (gc->allocations)
	{
		tmp = gc->allocations;
		gc->allocations = tmp->next;
		if (tmp->type == 0 && flag && tmp->value.fd != -1)
			close(tmp->value.fd);
		else if (tmp->type == 1)
			free(tmp->value.ptr);
		free(tmp);
	}
}

void	gc_malloc_fd(t_gc *gc, int fd)
{
	t_gc_node	*node;

	if (!gc)
		return ;
	node = malloc(sizeof(t_gc_node));
	if (!node)
		return ;
	node->value.fd = fd;
	node->type = 0;
	node->next = gc->allocations;
	gc->allocations = node;
}
