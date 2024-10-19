/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:03:34 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/19 18:17:25 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

t_sprites	load_sprites(void *mlx_ptr)
{
	t_sprites		sprites;
	t_dimension		dim;

	sprites.player = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/player.xpm", &dim.width, &dim.height);
	sprites.wall = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/wall.xpm", &dim.width, &dim.height);
	if (!sprites.wall)
		ft_printf("Error: Failed to load wall sprite\n");
	sprites.empty = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/empty.xpm", &dim.width, &dim.height);
	sprites.collectible = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/crate.xpm", &dim.width, &dim.height);
	sprites.exit = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/exit.xpm", &dim.width, &dim.height);
	sprites.free_exit = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/free_exit.xpm", &dim.width, &dim.height);
	if (!sprites.player || !sprites.wall || !sprites.empty
		|| !sprites.collectible || !sprites.exit || !sprites.free_exit)
	{
		write(2, "Error: Failed to load sprites\n", 30);
		exit(1);
	}
	return (sprites);
}

static void	*get_sprite_image(t_data *data, char tile, t_sprites sprites)
{
	if (tile == 'P')
		return (sprites.player);
	else if (tile == '1')
		return (sprites.wall);
	else if (tile == '0')
		return (sprites.empty);
	else if (tile == 'C')
		return (sprites.collectible);
	else if (tile == 'E')
	{
		if (data->crate_count == 0)
			return (sprites.free_exit);
		else
			return (sprites.exit);
	}
	return (NULL);
}

void	draw_map(char **map, t_data *data, t_sprites sprites)
{
	t_point		pos;
	void		*img;

	pos.y = 0;
	img = NULL;
	while (map[pos.y])
	{
		pos.x = 0;
		while (map[pos.y][pos.x])
		{
			img = get_sprite_image(data, map[pos.y][pos.x], sprites);
			if (img == NULL)
			{
				ft_printf("Error: Failed to load sprite for %c at (%d, %d)\n",
					map[pos.y][pos.x], pos.x, pos.y);
				continue;
			}
			if (img)
			{
				if (!data->mlx_ptr)
					ft_printf("Error: mlx_ptr is NULL\n");
				if (!data->win_ptr)
					ft_printf("Error: win_ptr is NULL\n");
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					img, pos.x * TILE_SIZE, pos.y * TILE_SIZE);
			}
			pos.x++;
		}
		pos.y++;
	}
}
