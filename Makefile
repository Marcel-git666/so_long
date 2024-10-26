# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 16:05:35 by mmravec           #+#    #+#              #
#    Updated: 2024/10/26 20:31:45 by mmravec          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

# Check for macOS or Linux and set CFLAGS and LIBS accordingly
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	CC = gcc-14
	CFLAGS = -Wall -Werror -Wextra -Iinclude -g -D__APPLE__ -DGL_SILENCE_DEPRECATION
	MLX_DIR = minilibx_macos
	FRAMEWORKS = -framework OpenGL -framework AppKit
	LIBS = -L$(MLX_DIR) -lmlx $(FRAMEWORKS)
else
	CC = cc
	CFLAGS = -Wall -Werror -Wextra -Iinclude -g -D__linux__
	MLX_DIR = minilibx_linux
	LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
endif

# Source files
SRCS_DIR = src
SRCS = $(SRCS_DIR)/main.c $(SRCS_DIR)/map.c $(SRCS_DIR)/graphics_init.c \
	$(SRCS_DIR)/draw_map.c $(SRCS_DIR)/move.c $(SRCS_DIR)/game_loop.c \
	$(SRCS_DIR)/sprites.c $(SRCS_DIR)/deinit.c
OBJS = $(SRCS:.c=.o)

# Path to the libft directory
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Rule to build the so_long executable
$(NAME): $(LIBFT) $(MLX_DIR)/libmlx.a $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft $(LIBS)

# Rule to build libft by calling its Makefile
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Rule to build MiniLibX
$(MLX_DIR)/libmlx.a:
	$(MAKE) -C $(MLX_DIR)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Default target to build everything (both server and client)
all: $(NAME)

# Clean up object files
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

# Clean up object files and the executables
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything from scratch
re: fclean all

.PHONY: all clean fclean re
