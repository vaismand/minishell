.SILENT:

SRCS	= ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memcpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memmove.c \
			ft_memset.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strchr.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_itoa.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_strmapi.c \
			ft_split.c \
			ft_striteri.c \
			ft_chartostr.c \
			ft_strndup.c \

SRCS_B	= ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \

OBJS	= ${SRCS:.c=.o}
OBJS_B  = ${SRCS_B:.c=.o}
NAME	= libft.a
LIBC	= ar rc
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror
INCS 	= .

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${INCS}

${NAME}: ${OBJS}
	@${LIBC} ${NAME} ${OBJS}

all: ${NAME}

bonus: ${NAME} ${OBJS_B}
	@${LIBC} ${NAME} ${OBJS_B}

fclean: clean
	@${RM} ${NAME} ${bonus}

clean:
	@${RM} -f ${OBJS} ${OBJS_B}

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader */*.[ch]

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS)
