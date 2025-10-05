/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omadali < omadali@student.42kocaeli.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:42:34 by omadali           #+#    #+#             */
/*   Updated: 2025/07/04 16:42:34 by omadali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "structs.h"

t_list	*build_command_list(t_token *tokens, t_shell *shell);
int		parse_input(char *input, t_shell *shell);

t_cmd	*parse_single_command(t_token **current, t_shell *shell);

t_redir	*add_redir_gc(t_redir **head, t_redir_info *info, t_gc *gc);
int		handle_redirection(t_token **tok, t_cmd *cmd, t_shell *shell);

t_list	*ft_lstnew_gc(void *content, t_gc *gc);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		is_all_spaces(const char *s);
int		count_args(t_token *start);

void	clear_redirs(t_redir *r);
void	clear_cmd_list(t_list *cmds);

#endif