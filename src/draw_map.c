/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:03:34 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/18 16:38:39 by mmravec          ###   ########.fr       */
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
	sprites.free_exit = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/free_exit.xpm", &dim.width, &dim.height);
	// sprites.digit_0 = mlx_xpm_file_to_image(mlx_ptr,
	// 		"sprites/numbers/resized.xpm", &dim.width, &dim.height);
	// if (!sprites.digit_0)
	// {
	// 	write(2, "Error: Failed to load 0.xpm\n", 29);
	// 	exit(1);
	// }
	sprites.digit_1 = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/numbers/1.xpm", &dim.width, &dim.height);
	if (!sprites.digit_1)
	{
		write(2, "Error: Failed to load 0.xpm\n", 29);
		exit(1);
	}
	sprites.digit_2 = mlx_xpm_file_to_image(mlx_ptr,
			"sprites/numbers/2.xpm", &dim.width, &dim.height);
	if (!sprites.digit_2)
	{
		write(2, "Error: Failed to load 0.xpm\n", 29);
		exit(1);
	}
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


// void	draw_number(t_data *data, int number, int x, int y)
// {
//     char	*str;
//     int		i;
//     void	*img;

//     str = ft_itoa(number);  // Convert the number to a string
// 	i = 0;
// 	ft_printf("Drawing %s to (%d, %d)\n", str, x, y);
// 	img = data->sprites.digit_1;
//     if (img)
//         mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, 10, 10);
//     else
//         ft_printf("Error: digit_0 image not loaded\n");

//     // Loop through the characters of the number and draw each corresponding digit
//     // while (str[i])
//     // {
//     //     if (str[i] == '0')
//     //         img = data->sprites.digit_0;
//     //     else if (str[i] == '1')
//     //         img = data->sprites.digit_1;
//     //     else if (str[i] == '2')
//     //         img = data->sprites.digit_2;
//     //     // Add else if blocks for other digits (3 to 9)

// 	// 	if (img)
//     //         mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img,
//     //             x + (i * 21), y);  // Draw each digit with 21-pixel spacing horizontally
// 	// 	ft_printf("Drawing image number: %d\n", i);
//     //     i++;
//     // }

// 	i++;
//     free(str);  // Free the allocated string from ft_itoa
// }

void	draw_map(char **map, t_data *data)
{
	t_point		pos;
	t_sprites	sprites;
	void		*img;

	sprites = load_sprites(data->mlx_ptr);
	ft_printf("Sprites loaded...\n");
	pos.y = 0;
	img = NULL;
	while (map[pos.y])
	{
		ft_printf("y:%d\n", pos.y);
		pos.x = 0;
		while (map[pos.y][pos.x])
		{
			img = get_sprite_image(data, map[pos.y][pos.x], sprites);
			if (img)
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					img, pos.x * TILE_SIZE, pos.y * TILE_SIZE);
			}
			pos.x++;
		}
		pos.y++;
	}
}
