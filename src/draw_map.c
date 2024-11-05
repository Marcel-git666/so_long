/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:47:58 by mmravec           #+#    #+#             */
/*   Updated: 2024/11/05 13:06:39 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

static void	*get_up_down_sprite(void *stand, void *walk, void *walk2, int frame)
{
	if (frame == 1 || frame == 4)
		return (stand);
	else if (frame == 2 || frame == 5)
		return (walk);
	return (walk2);
}

static void	*get_l_r_sprite(void *stand, void *walk, int frame)
{
	if (frame % 2 == 1)
		return (stand);
	return (walk);
}

void	*get_player_image(t_game *game, char direction, int frame)
{
	void	*current_sprite;

	current_sprite = NULL;
	if (direction == 'U')
		current_sprite = get_up_down_sprite(game->player_sprites->up_stand,
				game->player_sprites->up_walk,
				game->player_sprites->up_walk2, frame);
	else if (direction == 'D')
		current_sprite = get_up_down_sprite(game->player_sprites->down_stand,
				game->player_sprites->down_walk,
				game->player_sprites->down_walk2, frame);
	else if (direction == 'L')
		current_sprite = get_l_r_sprite(game->player_sprites->left_stand,
				game->player_sprites->left_walk, frame);
	else if (direction == 'R')
		current_sprite = get_l_r_sprite(game->player_sprites->right_stand,
				game->player_sprites->right_walk, frame);
	return (current_sprite);
}

void	*get_tile_image(t_game *game, char tile)
{
	void	*image;

	image = NULL;
	if (tile == 'P')
		image = get_player_image(game, game->data.last_direction,
				game->data.frame);
	else if (tile == '1')
		image = game->sprites->wall;
	else if (tile == '0')
		image = game->sprites->empty;
	else if (tile == 'C')
		image = game->sprites->collectible;
	else if (tile == 'E')
	{
		if (game->data.crate_count == 0)
			image = game->sprites->free_exit;
		else
			image = game->sprites->exit;
	}
	return (image);
}

void	draw_map(t_game *game)
{
	t_point	pos;
	void	*img;

	pos.y = 0;
	while (game->data.map[pos.y])
	{
		pos.x = 0;
		while (game->data.map[pos.y][pos.x])
		{
			img = get_tile_image(game, game->data.map[pos.y][pos.x]);
			if (img)
			{
				mlx_put_image_to_window(game->data.mlx_ptr, game->data.win_ptr,
					img, pos.x * TILE_SIZE, pos.y * TILE_SIZE);
			}
			pos.x++;
		}
		pos.y++;
	}
}
