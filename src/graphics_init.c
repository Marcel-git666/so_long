/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:12:14 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/26 18:48:01 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

// Function to handle key press events
int handle_keypress(int keycode, t_data *data)
{
	ft_printf("Key %d is pressed.\n", keycode);
	if (data->game_won)  // If the game is over, exit on any key press
	{
		// data->game_over = 1;
		mlx_loop_end(data->mlx_ptr);  // End the game loop
		return (0);
    }
	if (keycode == ESC_KEY)
	{
		data->game_over = 1;
		mlx_loop_end(data->mlx_ptr);
		return (0);
	}
	if (!data->game_over)
	{
		if (keycode == UP_KEY)
			move_player(data, 0, -1);
		else if (keycode == DOWN_KEY)
			move_player(data, 0, 1);
		else if (keycode == LEFT_KEY)
			move_player(data, -1, 0);
		else if (keycode == RIGHT_KEY)
			move_player(data, 1, 0);
	}
	return (0);
}


// Function to handle window close (cross click)
int	handle_exit(t_data *data)
{
	data->game_over = 1;
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

void	init_player_position(t_data *data, char **map)
{
	int		x;
	int		y;

	data->move_count = 0;
	data->crate_count = 0;
	data->game_over = 0;
	data->game_won = 0;
	data->needs_redraw = 1;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				data->player_pos.x = x;
				data->player_pos.y = y;
			}
			if (map[y][x] == 'C')
			{
				data->crate_pos.x = x;
				data->crate_pos.y = y;
				data->crate_count++;
			}
			x++;
		}
		y++;
	}
}

// Initialize graphics, create window, set event hooks
void	init_graphics(t_game *game)
{
	int		window_width;
	int		window_height;
	int		map_height;

	game->data.mlx_ptr = mlx_init();
	if (!game->data.mlx_ptr)
	{
		write(2, "Error: Unable to initialize MiniLibX\n", 37);
		exit(1);
	}
	map_height = 0;
	while (game->data.map[map_height])
		map_height++;
	window_width = ft_strlen(game->data.map[0]) * TILE_SIZE;
	window_height = map_height * TILE_SIZE;
	game->data.win_ptr = mlx_new_window(game->data.mlx_ptr, window_width,
			window_height, "so_long");
	if (!game->data.win_ptr)
	{
		write(2, "Error: Unable to create window\n", 31);
		exit(1);
	}
	init_player_position(&game->data, game->data.map);
	ft_printf("Ready to draw background.\n");
	draw_background(game);
	ft_printf("Graphics initialized.\n");
}

void free_sprites(t_game *game)
{
	ft_printf("Deestroying images...\n");
	if (game->sprites->player)
	{
		ft_printf("Destroying image player.\n");
		mlx_destroy_image(game->data.mlx_ptr, game->sprites->player);
	}
	if (game->sprites->wall)
	{
		mlx_destroy_image(game->data.mlx_ptr, game->sprites->wall);
		ft_printf("Destroying image wall.\n");
	}
	if (game->sprites->empty)
		mlx_destroy_image(game->data.mlx_ptr, game->sprites->empty);
	if (game->sprites->collectible)
		mlx_destroy_image(game->data.mlx_ptr, game->sprites->collectible);
	if (game->sprites->exit)
		mlx_destroy_image(game->data.mlx_ptr, game->sprites->exit);
	if (game->sprites->free_exit)
		mlx_destroy_image(game->data.mlx_ptr, game->sprites->free_exit);
	free(game->sprites);
}

void free_map(char **map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	deinit(char **map, char *file_content, t_game *game)
{
	ft_printf("Inside deinit function.\n");
	free_sprites(game);
	free_map(map);
	if (file_content)
		free(file_content);
	if (game->data.win_ptr)
		mlx_destroy_window(game->data.mlx_ptr, game->data.win_ptr);
	if (game->data.mlx_ptr)
		mlx_destroy_display(game->data.mlx_ptr);
	free(game);
}
