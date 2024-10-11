/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:03:34 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/11 21:31:04 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

#define TILE_SIZE 16  // Set the tile size (this should match the size of your sprites)

// Function to draw the map based on the .ber file
void draw_map(char **map, t_data *data)
{
    int x, y;
    int width, height;  // Declare width and height for the images
    void *img_player, *img_wall, *img_empty, *img_collectible, *img_exit;

	ft_putendl_fd("Loading player sprite...", 1);
	img_player = mlx_xpm_file_to_image(data->mlx_ptr, "sprites/1.xpm", &width, &height);
	if (!img_player)
	{
		write(2, "Error: Failed to load player sprite\n", 36);
		exit(1);
	}
	ft_putendl_fd("Player sprite loaded.", 1);

	// Load the images (sprites)
	img_player = mlx_xpm_file_to_image(data->mlx_ptr, "sprites/1.xpm", &width, &height);
	if (!img_player)
		write(2, "Error: Failed to load player sprites\n", 30);
    img_wall = mlx_xpm_file_to_image(data->mlx_ptr, "sprites/wall.xpm", &width, &height);
	if (!img_wall)
		write(2, "Error: Failed to load wall sprites\n", 30);
    img_empty = mlx_xpm_file_to_image(data->mlx_ptr, "sprites/2.xpm", &width, &height);
	if (!img_empty)
		write(2, "Error: Failed to load empty sprites\n", 37);
    img_collectible = mlx_xpm_file_to_image(data->mlx_ptr, "sprites/3.xpm", &width, &height);
	if (!img_collectible)
		write(2, "Error: Failed to load collectible sprites\n", 43);
    img_exit = mlx_xpm_file_to_image(data->mlx_ptr, "sprites/4.xpm", &width, &height);
	if (!img_exit)
		write(2, "Error: Failed to load exit sprites\n", 36);

    // Check if the images were loaded correctly
    if (!img_player || !img_wall || !img_empty || !img_collectible || !img_exit)
    {
        write(2, "Error: Failed to load sprites\n", 30);
        exit(1);
    }

    // Loop through the map and place the appropriate sprite
    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == 'P')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_player, x * TILE_SIZE, y * TILE_SIZE);
            else if (map[y][x] == '1')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_wall, x * TILE_SIZE, y * TILE_SIZE);
            else if (map[y][x] == '0')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_empty, x * TILE_SIZE, y * TILE_SIZE);
            else if (map[y][x] == 'C')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_collectible, x * TILE_SIZE, y * TILE_SIZE);
            else if (map[y][x] == 'E')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_exit, x * TILE_SIZE, y * TILE_SIZE);
            x++;
        }
        y++;
    }
}
