NAME = minishell
	
CC = cc
	
CFLAGS = -Wall -Wextra -Werror
	
SRCS = minishell.c \
	parser/parser.c \
	parser/command_parser.c \
	parser/redirection_parser.c \
	parser/parse_utils.c \
	parser/command_list.c \
	lexer/lexer.c \
	lexer/token__utils.c \
	lexer/word_collector.c \
	lexer/quote_handler.c \
	lexer/operator_handler.c \
	utils.c \
	executer/executer.c \
	executer/command_finder.c \
	executer/heredoc.c \
	executer/redirections.c \
	executer/pipeline.c \
	expander/variable_expander.c \
	expander/env_lookup.c \
	expander/strings_utils.c \
	builtins/builtins.c \
    builtins/cd.c \
	builtins/cd2.c \
    builtins/echo.c \
    builtins/env.c \
    builtins/exit.c \
    builtins/export.c \
    builtins/pwd.c \
    builtins/unset.c \
	builtins/export2.c \
	builtins/export3.c \
	signal.c \
	gc.c \
	gc1.c \
	libft/libftfc.c \
	libft/libftfc2.c \
	libft/libftfc3.c \
	libft/libftfc4.c \
	libft/libftfc5.c
	
OBJS = $(SRCS:.c=.o)
	
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline


clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)
	
re: fclean $(NAME)
	
.PHONY: all clean fclean re test