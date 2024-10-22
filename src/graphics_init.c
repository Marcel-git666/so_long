/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:12:14 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/22 16:20:52 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

// Function to handle key press events
int handle_keypress(int keycode, t_data *data)
{
	ft_printf("Key %d is pressed.\n", keycode);
	if (keycode == ESC_KEY)
	{
		data->game_over = 1;
		// mlx_loop_end(data->mlx_ptr);
		return (0);
	}
	if (keycode == UP_KEY && data->game_over == 0)
		move_player(data, 0, -1);
	else if (keycode == DOWN_KEY && data->game_over == 0)
		move_player(data, 0, 1);
	else if (keycode == LEFT_KEY && data->game_over == 0)
		move_player(data, -1, 0 && data->game_over == 0);
	else if (keycode == RIGHT_KEY && data->game_over == 0)
		move_player(data, 1, 0);
	return (0);
}


// Function to handle window close (cross click)
int	handle_exit(t_data *data)
{
	data->game_over = 1;
	// mlx_loop_end(data->mlx_ptr);
	return (0);
}

void	init_player_position(t_data *data, char **map)
{
	int		x;
	int		y;

	data->move_count = 0;
	data->crate_count = 0;
	data->game_over = 0;
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
void	init_graphics(t_data *data, char **map)
{
	int		window_width;
	int		window_height;
	int		map_height;

	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		write(2, "Error: Unable to initialize MiniLibX\n", 37);
		exit(1);
	}
	map_height = 0;
	while (map[map_height])
		map_height++;
	window_width = ft_strlen(map[0]) * TILE_SIZE;
	window_height = map_height * TILE_SIZE;
	data->win_ptr = mlx_new_window(data->mlx_ptr, window_width,
			window_height, "so_long");
	if (!data->win_ptr)
	{
		write(2, "Error: Unable to create window\n", 31);
		exit(1);
	}
	data->map = map;
	init_player_position(data, map);
}

void free_sprites(t_data *data)
{
	if (data->sprites.player)
		mlx_destroy_image(data->mlx_ptr, data->sprites.player);
	if (data->sprites.wall)
		mlx_destroy_image(data->mlx_ptr, data->sprites.wall);
	if (data->sprites.empty)
		mlx_destroy_image(data->mlx_ptr, data->sprites.empty);
	if (data->sprites.collectible)
		mlx_destroy_image(data->mlx_ptr, data->sprites.collectible);
	if (data->sprites.exit)
		mlx_destroy_image(data->mlx_ptr, data->sprites.exit);
	if (data->sprites.free_exit)
		mlx_destroy_image(data->mlx_ptr, data->sprites.free_exit);
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
	free_sprites(&game->data);
	free_map(map);
	if (file_content)
		free(file_content);
	if (game->data.win_ptr)
		mlx_destroy_window(game->data.mlx_ptr, game->data.win_ptr);
	// if (game->data.mlx_ptr)
	// 	mlx_destroy_display(game->data.mlx_ptr);
}
