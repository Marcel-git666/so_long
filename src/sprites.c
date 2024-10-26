/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:25:09 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/26 20:34:41 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

t_sprites	*load_sprites(void *mlx_ptr)
{
	t_sprites		*sprites;
	t_dimension		dim;

	ft_printf("Loading sprites....\n");
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
	return (sprites);
}
t_player_sprites *load_player_sprites(void *mlx_ptr)
{
	t_player_sprites *player_sprites;
    t_dimension dim;

    ft_printf("Loading player sprites....\n");
    player_sprites = malloc(sizeof(t_player_sprites));
    if (!player_sprites) {
        write(2, "Error: Failed to allocate memory for player sprites\n", 52);
        exit(1);
    }

    // Load each player sprite and handle potential errors
    player_sprites->up_stand = mlx_xpm_file_to_image(mlx_ptr, "sprites/player_up_stand.xpm", &dim.width, &dim.height);
    player_sprites->up_walk = mlx_xpm_file_to_image(mlx_ptr, "sprites/player_up_walk.xpm", &dim.width, &dim.height);
    player_sprites->up_walk2 = mlx_xpm_file_to_image(mlx_ptr, "sprites/player_up_walk2.xpm", &dim.width, &dim.height);

    player_sprites->down_stand = mlx_xpm_file_to_image(mlx_ptr, "sprites/player_down_stand.xpm", &dim.width, &dim.height);
    player_sprites->down_walk = mlx_xpm_file_to_image(mlx_ptr, "sprites/player_down_walk.xpm", &dim.width, &dim.height);
    player_sprites->down_walk2 = mlx_xpm_file_to_image(mlx_ptr, "sprites/player_down_walk2.xpm", &dim.width, &dim.height);

    player_sprites->left_stand = mlx_xpm_file_to_image(mlx_ptr, "sprites/player_left_stand.xpm", &dim.width, &dim.height);
    player_sprites->left_walk = mlx_xpm_file_to_image(mlx_ptr, "sprites/player_left_walk.xpm", &dim.width, &dim.height);

    player_sprites->right_stand = mlx_xpm_file_to_image(mlx_ptr, "sprites/player_right_stand.xpm", &dim.width, &dim.height);
    player_sprites->right_walk = mlx_xpm_file_to_image(mlx_ptr, "sprites/player_right_walk.xpm", &dim.width, &dim.height);

    // Check if all sprites were loaded successfully
    if (!player_sprites->up_stand || !player_sprites->up_walk || !player_sprites->up_walk2 ||
        !player_sprites->down_stand || !player_sprites->down_walk || !player_sprites->down_walk2 ||
        !player_sprites->left_stand || !player_sprites->left_walk ||
        !player_sprites->right_stand || !player_sprites->right_walk) {
		write(2, "Error: Failed to load one or more player sprites\n", 49);
		free(player_sprites);
		exit(1);
	}
	ft_printf("Player sprites loaded successfully.\n");
	return (player_sprites);
}
