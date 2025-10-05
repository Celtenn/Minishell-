/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idkahram <idkahram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:00:00 by omadali           #+#    #+#             */
/*   Updated: 2025/07/21 03:41:21 by idkahram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	int				in_herodocc;
}	t_token;

typedef struct s_tokenizer_state
{
	char	*input;
	int		*i;
	t_token	**tokens;
	int		*in_heredoc;
}	t_tokenizer_state;

typedef struct s_redir
{
	char			*filename;
	int				type;
	int				quoted_delim;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_redir_info
{
	char	*filename;
	int		type;
	int		quoted;
}	t_redir_info;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirs;
	int				pipe_next;
}	t_cmd;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_collector_state
{
	char			**result;
	struct s_shell	*shell;
	int				in_heredoc;
	int				mark_empty;
}	t_collector_state;

#endif