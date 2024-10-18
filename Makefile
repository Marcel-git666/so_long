# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 16:05:35 by mmravec           #+#    #+#              #
#    Updated: 2024/10/18 20:16:21 by mmravec          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iinclude -g
# -D__linux__

# Source files
SRCS_DIR = src
SRCS = $(SRCS_DIR)/main.c $(SRCS_DIR)/map.c $(SRCS_DIR)/graphics_init.c \
	$(SRCS_DIR)/draw_map.c $(SRCS_DIR)/move.c $(SRCS_DIR)/game_loop.c
OBJS = $(SRCS:.c=.o)

# Path to the libft directory
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Path to MiniLibX
MLX_DIR = minilibx_linux
MLX = $(MLX_DIR)/libmlx.a

# Link necessary macOS frameworks for graphics
FRAMEWORKS = -framework OpenGL -framework AppKit
FRAMEWORKS_linux = -lXext -lX11 -lm -lz

# Rule to build the so_long executable
$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx $(FRAMEWORKS_linux)

# Rule to build libft by calling its Makefile
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Rule to build MiniLibX
$(MLX):
	$(MAKE) -C $(MLX_DIR)

# Rule to compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Default target to build everything (both server and client)
all: $(NAME)

# Clean up object files
clean:
	rm -f $(OBJS) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

# Clean up object files and the executables
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything from scratch
re: fclean all

.PHONY: all clean fclean re
