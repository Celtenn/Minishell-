/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:42:34 by omadali           #+#    #+#             */
/*   Updated: 2025/07/04 16:42:34 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "structs.h"

int		is_special(char c);
char	*gc_realloc(t_gc *gc, char *old, size_t new_size);
t_token	*add_token(t_tokenizer_state *haha, const char *val,
			t_token_type type, t_gc *gc);
void	skip_spaces(char *input, int *i);

int		handle_quotes(const char *input, int i, char **out, t_gc *gc);
int		handle_double_quotes(const char *input, int *i,
			t_collector_state *state);
int		handle_single_quotes(const char *input, int *i,
			t_collector_state *state);
int		handle_unquoted_segment(const char *input, int *i,
			t_collector_state *state);

char	*collect_word_segments(const char *input, int *i,
			t_shell *shell, int in_heredoc);
int		append_processed_segment(char **result, const char *segment,
			t_shell *shell);

int		handle_operator(char *input, int *i, t_tokenizer_state *nana,
			t_shell *shell);

t_token	*tokenize(char *input, t_shell *shell);

#endif