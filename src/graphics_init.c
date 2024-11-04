/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:12:14 by mmravec           #+#    #+#             */
/*   Updated: 2024/11/04 20:24:24 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

void	init_player_position(t_data *data, char **map)
{
	int		x;
	int		y;

	data->move_count = 0;
	data->crate_count = 0;
	data->game_over = 0;
	data->game_won = 0;
	data->needs_redraw = 1;
	data->last_direction = 'R';
	data->frame = 1;
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

	ft_printf("Graphics starts to init.\n");
	game->data.mlx_ptr = mlx_init();
	if (!game->data.mlx_ptr)
	{
		write(2, "Error: Unable to initialize MiniLibX\n", 37);
		exit(1);
	}
	if (!game->data.map)
	{
		write(2, "Error: Map is NULL.\n", 20);
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
}
