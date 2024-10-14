/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:03:34 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/14 11:23:26 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

static t_sprites	load_sprites(void *mlx_ptr)
{
	t_sprites		sprites;
	t_dimension		dim;

	sprites.player = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/player.xpm", &dim.width, &dim.height);
	sprites.wall = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/wall.xpm", &dim.width, &dim.height);
	sprites.empty = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/empty.xpm", &dim.width, &dim.height);
	sprites.collectible = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/crate.xpm", &dim.width, &dim.height);
	sprites.exit = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/exit.xpm", &dim.width, &dim.height);
	if (!sprites.player || !sprites.wall || !sprites.empty
		|| !sprites.collectible || !sprites.exit)
	{
		write(2, "Error: Failed to load sprites\n", 30);
		exit(1);
	}
	return (sprites);
}

static void	*get_sprite_image(char tile, t_sprites sprites)
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
		return (sprites.exit);
	return (NULL);
}

void	draw_map(char **map, t_data *data)
{
	t_point		pos;
	t_sprites	sprites;
	void		*img;

	sprites = load_sprites(data->mlx_ptr);
	pos.y = 0;
	img = NULL;
	while (map[pos.y])
	{
		pos.x = 0;
		while (map[pos.y][pos.x])
		{
			img = get_sprite_image(map[pos.y][pos.x], sprites);
			if (img)
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					img, pos.x * TILE_SIZE, pos.y * TILE_SIZE);
				ft_printf("Drawing tile %c at (%d, %d)\n", map[pos.y][pos.x], pos.x, pos.y);
			}
			pos.x++;
		}
		pos.y++;
	}
}
