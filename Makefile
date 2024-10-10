# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 16:05:35 by mmravec           #+#    #+#              #
#    Updated: 2024/10/10 18:37:53 by mmravec          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = gcc-14
CFLAGS = -Wall -Werror -Wextra

# Source files for the server
SRCS = main.c
OBJS = $(SRCS:.c=.o)

# Path to the libft directory
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Rule to build the final server executable
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft

# Rule to build libft by calling its Makefile
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Default target to build everything (both server and client)
all: $(NAME)

# Clean up object files
clean:
	rm -f $(OBJS) $(OBJS)

# Clean up object files and the executables
fclean: clean
	rm -f $(NAME)

# Rebuild everything from scratch
re: fclean all

.PHONY: all clean fclean re
