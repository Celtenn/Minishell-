/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/08/04 00:31:34 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/lexer.h"
#include "../headers/expander.h"

static char	*handle_dollar_sign(const char *input, int *i, t_shell *shell,
								char *result)
{
	char	*new_result;
	char	*exit_str;

	(*i)++;
	if (input[*i] == '?')
	{
		(*i)++;
		exit_str = ft_itoa(shell->exit_status);
		new_result = append_to_result(shell->gc, result, exit_str);
		free(exit_str);
	}
	else if (ft_isalnum((unsigned char)input[*i]) || input[*i] == '_')
	{
		new_result = expand_env_var(input, i, shell, result);
		if (!new_result)
			new_result = result;
	}
	else
	{
		new_result = append_to_result(shell->gc, result, "$");
	}
	return (new_result);
}

static char	*expand_tilde(const char *input, t_shell *shell)
{
	char	*home_dir;
	char	*result;

	home_dir = get_var_value("HOME", shell);
	if (!home_dir || *home_dir == '\0')
	{
		free(home_dir);
		return (gc_strdup(shell->gc, input));
	}
	if (input[1] == '\0')
		result = gc_strdup(shell->gc, home_dir);
	else if (input[1] == '/')
	{
		result = gc_malloc(shell->gc, ft_strlen(home_dir) + ft_strlen(input));
		ft_memcpy(result, home_dir, ft_strlen(home_dir));
		ft_strcat(result, input + 1);
	}
	else
		result = gc_strdup(shell->gc, input);
	free(home_dir);
	return (result);
}

static char	*build_expanded_string(const char *input, t_shell *shell)
{
	char	*result;
	int		i;

	result = gc_malloc(shell->gc, 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1])
		{
			result = handle_dollar_sign(input, &i, shell, result);
			if (!result)
				return (NULL);
		}
		else
		{
			result = append_char_to_result(shell->gc, result, input[i]);
			i++;
		}
	}
	return (result);
}

static char	*expand_and_split_if_needed(char *result, t_shell *shell)
{
	char				**parts;
	t_tokenizer_state	tmp_state;
	int					fake_heredoc;
	int					j;

	if (!ft_strchr(result, ' '))
		return (result);
	parts = ft_split(result, ' ');
	if (!parts)
		return (gc_strdup(shell->gc, ""));
	tmp_state.tokens = shell->tokens;
	fake_heredoc = 0;
	tmp_state.in_heredoc = &fake_heredoc;
	j = 0;
	while (parts[j])
		add_token(&tmp_state, parts[j++], T_WORD, shell->gc);
	free_str_array(parts);
	return (gc_strdup(shell->gc, ""));
}

char	*expand_variables(const char *input, t_shell *shell, int flag)
{
	char	*result;

	if (!input)
		return (NULL);
	if (!flag || shell->quoted)
		return (gc_strdup(shell->gc, input));
	if (input[0] == '~')
		return (expand_tilde(input, shell));
	if (!ft_strchr(input, '$'))
		return (gc_strdup(shell->gc, input));
	result = build_expanded_string(input, shell);
	if (!result)
		return (gc_strdup(shell->gc, ""));
	if (result[0] == '\0' && is_single_var_reference(input))
		return (gc_strdup(shell->gc, ""));
	return (expand_and_split_if_needed(result, shell));
}
