# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 14:23:01 by dvaisman          #+#    #+#              #
#    Updated: 2024/03/13 19:14:27 by dvaisman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

CFLAGS    = -Wall -Wextra -Werror
NAME      = minishell
SRCS = src/minishell.c \
		src/kv_signal.c \
		src/kv_parser.c \
		src/kv_parser_utils.c \
		src/kv_envp_actions.c \
		src/kv_execute.c \
		src/kv_builtins.c \
		src/kv_builtins2.c \
		src/kv_builtins3.c \
		src/kv_builtins_utils.c \
		src/kv_pipex.c \
		src/kv_pipex_utils.c \
		src/kv_file_opening.c \
		src/kv_split_quotes.c \
		src/kv_heredoc.c \
		src/kv_utils.c \
		src/kv_utils2.c \
		src/kv_utils3.c \
		src/kv_free_exit.c \


OBJS := $(SRCS:.c=.o)
LIBFT     = ./lib/libft/libft.a
CC        = cc
RM        = rm -f

RED       = \033[0;91m
GREEN     = \033[1;92m
BLUE      = \033[0;94m

all: ${NAME}

${NAME}: ${OBJS}
	@${MAKE} -s -C ./lib/libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@echo "${GREEN}Compilation is done!"

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

fclean: clean
	@${MAKE} clean -s -C ./lib/libft
	@${RM} ${NAME}
	@echo "${BLUE}Cleaning is done!"

clean:
	@${MAKE} fclean -s -C ./lib/libft
	@${RM} ${OBJS}

re: fclean all

.PHONY: all clean fclean re
