/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:55:59 by mmravec           #+#    #+#             */
/*   Updated: 2024/11/05 13:01:51 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

void	load_up_sprites(t_player_sprites *player_sprites, void *mlx_ptr,
			t_dimension *dim)
{
	player_sprites->up_stand = load_sprite(mlx_ptr,
			"sprites/player_up_stand.xpm", dim);
	player_sprites->up_walk = load_sprite(mlx_ptr,
			"sprites/player_up_walk.xpm", dim);
	player_sprites->up_walk2 = load_sprite(mlx_ptr,
			"sprites/player_up_walk2.xpm", dim);
	if (!player_sprites->up_stand || !player_sprites->up_walk
		|| !player_sprites->up_walk2)
	{
		write(2, "Error: Failed to load up sprites\n", 33);
		free(player_sprites);
		exit(1);
	}
}

void	load_down_sprites(t_player_sprites *player_sprites, void *mlx_ptr,
		t_dimension *dim)
{
	player_sprites->down_stand = load_sprite(mlx_ptr,
			"sprites/player_down_stand.xpm", dim);
	player_sprites->down_walk = load_sprite(mlx_ptr,
			"sprites/player_down_walk.xpm", dim);
	player_sprites->down_walk2 = load_sprite(mlx_ptr,
			"sprites/player_down_walk2.xpm", dim);
	if (!player_sprites->down_stand || !player_sprites->down_walk
		|| !player_sprites->down_walk2)
	{
		write(2, "Error: Failed to load down sprites\n", 35);
		free(player_sprites);
		exit(1);
	}
}

void	load_left_sprites(t_player_sprites *player_sprites, void *mlx_ptr,
	t_dimension *dim)
{
	player_sprites->left_stand = load_sprite(mlx_ptr,
			"sprites/player_left_stand.xpm", dim);
	player_sprites->left_walk = load_sprite(mlx_ptr,
			"sprites/player_left_walk.xpm", dim);
	if (!player_sprites->left_stand || !player_sprites->left_walk)
	{
		write(2, "Error: Failed to load left sprites\n", 35);
		free(player_sprites);
		exit(1);
	}
}

void	load_right_sprites(t_player_sprites *player_sprites, void *mlx_ptr,
	t_dimension *dim)
{
	player_sprites->right_stand = load_sprite(mlx_ptr,
			"sprites/player_right_stand.xpm", dim);
	player_sprites->right_walk = load_sprite(mlx_ptr,
			"sprites/player_right_walk.xpm", dim);
	if (!player_sprites->right_stand || !player_sprites->right_walk)
	{
		write(2, "Error: Failed to load right sprites\n", 36);
		free(player_sprites);
		exit(1);
	}
}

t_player_sprites	*load_player_sprites(void *mlx_ptr)
{
	t_player_sprites	*player_sprites;
	t_dimension			dim;

	player_sprites = malloc(sizeof(t_player_sprites));
	if (!player_sprites)
	{
		write(2, "Error: Failed to allocate memory for player sprites\n", 52);
		exit(1);
	}
	load_up_sprites(player_sprites, mlx_ptr, &dim);
	load_down_sprites(player_sprites, mlx_ptr, &dim);
	load_left_sprites(player_sprites, mlx_ptr, &dim);
	load_right_sprites(player_sprites, mlx_ptr, &dim);
	ft_printf("Player sprites loaded successfully.\n");
	return (player_sprites);
}
