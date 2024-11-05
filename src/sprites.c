/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:25:09 by mmravec           #+#    #+#             */
/*   Updated: 2024/11/05 13:05:55 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

void	*load_sprite(void *mlx_ptr, char *file_path, t_dimension *dim)
{
	void	*image;

	image = mlx_xpm_file_to_image(mlx_ptr, file_path, &dim->width,
			&dim->height);
	if (!image)
	{
		ft_printf("Error: Failed to load sprite %s\n", file_path);
	}
	return (image);
}

t_sprites	*load_sprites(void *mlx_ptr)
{
	t_sprites	*sprites;
	t_dimension	dim;

	ft_printf("Loading sprites....\n");
	sprites = malloc(sizeof(t_sprites));
	if (!sprites)
	{
		write(2, "Error: Failed to allocate memory for sprites\n", 46);
		exit(1);
	}
	sprites->wall = load_sprite(mlx_ptr, "sprites/wall.xpm", &dim);
	sprites->empty = load_sprite(mlx_ptr, "sprites/empty.xpm", &dim);
	sprites->collectible = load_sprite(mlx_ptr, "sprites/crate.xpm", &dim);
	sprites->exit = load_sprite(mlx_ptr, "sprites/exit.xpm", &dim);
	sprites->free_exit = load_sprite(mlx_ptr, "sprites/free_exit.xpm", &dim);
	if (!sprites->wall || !sprites->empty || !sprites->collectible
		|| !sprites->exit || !sprites->free_exit)
	{
		write(2, "Error: Failed to load one or more sprites\n", 41);
		free(sprites);
		exit(1);
	}
	return (sprites);
}
