/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idkahram <idkahram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/08/03 21:04:44 by idkahram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"
# include "gc.h"

char	*expand_variables(const char *input, t_shell *shell, int flag);

char	*get_var_value(const char *name, t_shell *shell);
char	*expand_exit_status(t_gc *gc, char *result, int *i);
char	*expand_env_var(const char *input, int *i, t_shell *shell,
			char *result);

char	*append_to_result(t_gc *gc, char *result, const char *append);
char	*append_char_to_result(t_gc *gc, char *result, char c);
int		is_single_var_reference(const char *input);

#endif