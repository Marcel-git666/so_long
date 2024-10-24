/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:03:34 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/24 20:29:28 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

t_sprites	*load_sprites(void *mlx_ptr)
{
	t_sprites		*sprites;
	t_dimension		dim;

	sprites = malloc(sizeof(t_sprites));
	if (!sprites)
	{
		write(2, "Error: Failed to allocate memory for sprites\n", 46);
		exit(1);
	}
	sprites->player = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/player.xpm", &dim.width, &dim.height);
	sprites->wall = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/wall.xpm", &dim.width, &dim.height);
	if (!sprites->wall)
		ft_printf("Error: Failed to load wall sprite\n");
	else
		ft_printf("Wall image: %p, width: %d, height: %d\n", sprites->wall, dim.width, dim.height);

	sprites->empty = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/empty.xpm", &dim.width, &dim.height);
	sprites->collectible = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/crate.xpm", &dim.width, &dim.height);
	sprites->exit = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/exit.xpm", &dim.width, &dim.height);
	sprites->free_exit = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/free_exit.xpm", &dim.width, &dim.height);
	if (!sprites->player || !sprites->wall || !sprites->empty
		|| !sprites->collectible || !sprites->exit || !sprites->free_exit)
	{
		write(2, "Error: Failed to load sprites\n", 30);
		free(sprites);
		exit(1);
	}
	ft_printf("Player image: %p\n", sprites->player);
	ft_printf("Wall image: %p\n", sprites->wall);
	ft_printf("Empty image: %p\n", sprites->empty);
	ft_printf("Collectible image: %p\n", sprites->collectible);
	ft_printf("Exit image: %p\n", sprites->exit);
	ft_printf("Free exit image: %p\n", sprites->free_exit);

	return (sprites);
}

static void	*get_sprite_image(t_data *data, char tile, t_sprites *sprites)
{
	if (tile == 'P')
		return (sprites->player);
	else if (tile == '1')
		return (sprites->wall);
	else if (tile == '0')
		return (sprites->empty);
	else if (tile == 'C')
		return (sprites->collectible);
	else if (tile == 'E')
	{
		if (data->crate_count == 0)
			return (sprites->free_exit);
		else
			return (sprites->exit);
	}
	return (NULL);
}

void	draw_map(t_game *game)
{
	t_point		pos;
	void		*img;

	ft_printf("Trying to draw a map.\n");
	ft_printf("mlx_ptr: %p\n", game->data.mlx_ptr);
	ft_printf("win_ptr: %p\n", game->data.win_ptr);
	pos.y = 0;
	img = NULL;
	while (game->data.map[pos.y])
	{
		pos.x = 0;
		while (game->data.map[pos.y][pos.x])
		{
			// ft_printf("xy: %d%d\n", pos.x, pos.y);
			img = get_sprite_image(&game->data, game->data.map[pos.y][pos.x], game->sprites);
			// ft_printf("img: %p\n", img);
			// ft_printf("sprites->wall: %p\n", game->sprites->wall);
			if (img == NULL)
			{
				ft_printf("Error: Failed to load sprite for %c at (%d, %d)\n",
					game->data.map[pos.y][pos.x], pos.x, pos.y);
				continue;
			}
			// if (!img || !game->data.mlx_ptr || !game->data.win_ptr)
			// {
			// 	ft_printf("Invalid pointer: img = %p, mlx_ptr = %p, win_ptr = %p\n",
			// 		img, game->data.mlx_ptr, game->data.win_ptr);
			// 	return;  // Skip drawing to avoid a crash
			// }
			if (img)
			{
				if (!game->data.mlx_ptr)
					ft_printf("Error: mlx_ptr is NULL\n");
				if (!game->data.win_ptr)
					ft_printf("Error: win_ptr is NULL\n");
				// ft_printf("Putting image to mlx_ptr: %p\n", game->data.mlx_ptr);
				if (game->data.mlx_ptr && game->data.win_ptr && img)
				{
					mlx_put_image_to_window(game->data.mlx_ptr, game->data.win_ptr,
						img, pos.x * TILE_SIZE, pos.y * TILE_SIZE);
				}
				else
				{
					ft_printf("Error: Invalid pointer detected. mlx_ptr: %p, win_ptr: %p, img: %p\n",
						game->data.mlx_ptr, game->data.win_ptr, img);
				}
			}
			pos.x++;
		}
		pos.y++;
	}
	ft_printf("Finished drawing a map.\n");
}
