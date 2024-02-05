# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkohn <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 17:29:31 by dkohn             #+#    #+#              #
#    Updated: 2024/02/05 20:22:29 by dkohn            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Define the source and object directories
SRCDIR = srcs
OBJDIR = obj

# Define the compiler and compiler flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

RED       = \033[0;91m
GREEN     = \033[1;92m
BLUE      = \033[0;94m

# Define the target name
NAME = libft.a

# Automatically find all source files in the "srcs" directory
SOURCES = srcs/ft_atoi.c \
			srcs/ft_bzero.c \
			srcs/ft_calloc.c \
			srcs/ft_isalnum.c \
			srcs/ft_isalpha.c \
			srcs/ft_isascii.c \
			srcs/ft_isdigit.c \
			srcs/ft_isprint.c \
			srcs/ft_itoa.c \
			srcs/ft_lstadd_back.c \
			srcs/ft_lstadd_front.c \
			srcs/ft_lstclear.c \
			srcs/ft_lstlast.c \
			srcs/ft_lstsize.c \
			srcs/ft_memcmp.c \
			srcs/ft_memcpy.c \
			srcs/ft_memset.c \
			srcs/ft_memmove.c \
			srcs/ft_print_hex.c \
			srcs/ft_print_ptr.c \
			srcs/ft_print_unsigned.c \
			srcs/ft_print_utils.c \
			srcs/ft_printf.c \
			srcs/ft_putchar_fd.c \
			srcs/ft_putendl_fd.c \
			srcs/ft_putnbr_fd.c \
			srcs/ft_putstr_fd.c \
			srcs/ft_split.c \
			srcs/ft_strchr.c \
			srcs/ft_strcmp.c \
			srcs/ft_strdup.c \
			srcs/ft_strjoin.c \
			srcs/ft_strlcat.c \
			srcs/ft_strlcpy.c \
			srcs/ft_strlen.c \
			srcs/ft_strmapi.c \
			srcs/ft_strncmp.c \
			srcs/ft_strnstr.c \
			srcs/ft_strrchr.c \
			srcs/ft_strtrim.c \
			srcs/ft_substr.c \
			srcs/ft_tolower.c \
			srcs/ft_toupper.c \
			srcs/get_next_line.c \

# Generate object file names in the "obj" directory from source files
OBJECTS	= $(SOURCES:.c=.o)

# Phony targets
.PHONY: all clean fclean re

# Default target to build the library
all: $(NAME)

# Rule to create the "obj" directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Rule to compile source files into object files with explicit dependencies
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Build the library from object files
$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)
	@echo "${GREEN}LIBFT Compilation is done!"

# Clean target to remove object files
clean:
	rm -rf $(OBJDIR) $(OBJECTS)

# Full clean target to remove object files and the library
fclean: clean
	rm -f $(NAME)


# Rebuild the library
re: fclean all