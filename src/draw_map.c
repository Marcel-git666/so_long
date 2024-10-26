/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:03:34 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/26 21:53:48 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

void	*get_player_image(t_game *game, char direction, int frame)
{
    void *current_sprite = NULL;

    if (direction == 'U') {  // Up
        if (frame == 1 || frame == 4) current_sprite = game->player_sprites->up_stand;
        else if (frame == 2 || frame == 5) current_sprite = game->player_sprites->up_walk;
        else if (frame == 3 || frame == 6) current_sprite = game->player_sprites->up_walk2;
    } else if (direction == 'D') {  // Down
        if (frame == 1 || frame == 4) current_sprite = game->player_sprites->down_stand;
        else if (frame == 2 || frame == 5) current_sprite = game->player_sprites->down_walk;
        else if (frame == 3 || frame == 6) current_sprite = game->player_sprites->down_walk2;
    } else if (direction == 'L') {  // Left
        if (frame % 2 == 1) current_sprite = game->player_sprites->left_stand;
        else current_sprite = game->player_sprites->left_walk;
    } else if (direction == 'R') {  // Right
        if (frame % 2 == 1) current_sprite = game->player_sprites->right_stand;
        else current_sprite = game->player_sprites->right_walk;
    }

    return current_sprite;
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

void draw_background(t_game *game) {
	t_point pos;
	void *img;

	pos.y = 0;
	while (game->data.map[pos.y]) {
        pos.x = 0;
        while (game->data.map[pos.y][pos.x]) {
            if (game->data.map[pos.y][pos.x] == '1')  // Assuming '1' is wall
                img = game->sprites->wall;
            else
                img = game->sprites->empty;  // '0' or empty spaces

            mlx_put_image_to_window(game->data.mlx_ptr, game->data.win_ptr,
                                    img, pos.x * TILE_SIZE, pos.y * TILE_SIZE);
            pos.x++;
        }
        pos.y++;
    }
}

void draw_foreground(t_game *game)
{
    t_point pos;
    void *img;

	ft_printf("Ready to draw foreground.\n");
    pos.y = 0;
    while (game->data.map[pos.y])
	{
        pos.x = 0;
        while (game->data.map[pos.y][pos.x])
		{
            if (game->data.map[pos.y][pos.x] == 'P') {
                // Get animated player sprite
                img = get_player_image(game, game->data.last_direction, game->data.frame);
				ft_printf("Position[%d, %d]: getting player image.\n", pos.x, pos.y);
            } else {
                // Get other sprites for non-player tiles
                img = get_sprite_image(&game->data, game->data.map[pos.y][pos.x], game->sprites);
				ft_printf("Position[%d, %d]: getting %c image.\n", pos.x, pos.y, game->data.map[pos.y][pos.x]);
            }
            if (img) {
                mlx_put_image_to_window(game->data.mlx_ptr, game->data.win_ptr,
                                        img, pos.x * TILE_SIZE, pos.y * TILE_SIZE);
            }
            pos.x++;
        }
        pos.y++;
    }
}
