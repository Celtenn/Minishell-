/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:01:46 by omadali           #+#    #+#             */
/*   Updated: 2025/07/14 20:01:46 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stdlib.h>

typedef union u_value
{
	int		fd;
	void	*ptr;
}	t_value;

typedef struct s_gc_node
{
	t_value				value;
	int					type;
	struct s_gc_node	*next;
}	t_gc_node;

typedef struct s_gc
{
	t_gc_node	*allocations;
}	t_gc;

t_gc	*gc_init(void);
void	*gc_malloc(t_gc *gc, size_t size);
char	*gc_strdup(t_gc *gc, const char *s);
void	gc_free_all(t_gc *gc, int flag);
void	gc_destroy(t_gc *gc, int flag);
t_gc	*get_set_gc(t_gc *new_gc);
void	gc_malloc_fd(t_gc *gc, int fd);

#endif
