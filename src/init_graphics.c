/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:12:14 by mmravec           #+#    #+#             */
/*   Updated: 2024/11/05 20:30:13 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

void	calculate_map_dimensions(t_data *data, int *width, int *height)
{
	int		map_height;

	map_height = 0;
	while (data->map[map_height])
		map_height++;
	*width = ft_strlen(data->map[0]) * TILE_SIZE;
	*height = map_height * TILE_SIZE;
}

static void	initialize_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		write(2, "Error: Unable to initialize MiniLibX\n", 37);
		exit(1);
	}
	if (!data->map)
	{
		write(2, "Error: Map is NULL.\n", 20);
		exit(1);
	}
}

static void	create_window(t_data *data, int width, int height)
{
	data->win_ptr = mlx_new_window(data->mlx_ptr, width, height, "so_long");
	if (!data->win_ptr)
	{
		write(2, "Error: Unable to create window\n", 31);
		exit(1);
	}
}

void	init_graphics(t_game *game)
{
	int		window_width;
	int		window_height;

	initialize_mlx(&game->data);
	calculate_map_dimensions(&game->data, &window_width, &window_height);
	create_window(&game->data, window_width, window_height);
	init_player_position(&game->data, game->data.map);
}
