.SILENT:

CFLAGS    = -Wall -Wextra -Werror
NAME      = minishell
SRCS = src/minishell.c


OBJS := $(SRCS:.c=.o)
LIBFT     = ./lib/libft/libft.a
CC        = cc -g
RM        = rm -f

RED       = \033[0;91m
GREEN     = \033[1;92m
BLUE      = \033[0;94m

all: ${NAME}

${NAME}: ${OBJS}
	@${MAKE} -s -C ./lib/libft > /dev/null
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@echo "${GREEN}Compilation is done!"

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

fclean: clean
	@${RM} ${NAME}
	@echo "${BLUE}Cleaning is done!"

clean:
	@${MAKE} clean -s -C ./lib/libft
	@${RM} ${OBJS}

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader */*.[ch]

.PHONY: all clean fclean re norm .c.o
