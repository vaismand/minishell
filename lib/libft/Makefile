# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkohn <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 17:29:31 by dkohn             #+#    #+#              #
#    Updated: 2023/12/14 16:42:35 by dkohn            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Define the source and object directories
SRCDIR = srcs
OBJDIR = obj

# Define the compiler and compiler flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Define the target name
NAME = libft.a

# Automatically find all source files in the "srcs" directory
SOURCES = $(wildcard $(SRCDIR)/*.c)

# Generate object file names in the "obj" directory from source files
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

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

# Clean target to remove object files
clean:
	rm -rf $(OBJDIR)

# Full clean target to remove object files and the library
fclean: clean
	rm -f $(NAME)

# Rebuild the library
re: fclean all