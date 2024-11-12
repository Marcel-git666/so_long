# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/03 16:05:35 by mmravec           #+#    #+#              #
#    Updated: 2024/11/12 14:43:20 by mmravec          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
CFLAGS = -Wall -Werror -Wextra -Iinclude -g
MLX_DIR = minilibx_linux
LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# Source files
SRCS_DIR = src
SRCS = $(SRCS_DIR)/main.c $(SRCS_DIR)/map.c $(SRCS_DIR)/init_graphics.c \
	$(SRCS_DIR)/draw_map.c $(SRCS_DIR)/move.c $(SRCS_DIR)/game_loop.c \
	$(SRCS_DIR)/sprites.c $(SRCS_DIR)/deinit.c $(SRCS_DIR)/init_player.c \
	$(SRCS_DIR)/handle.c $(SRCS_DIR)/sprites_player.c $(SRCS_DIR)/open_file.c \
	$(SRCS_DIR)/move_count.c $(SRCS_DIR)/map_path.c \
	$(SRCS_DIR)/map_path_utils.c
	
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
