/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:12:31 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/24 21:03:53 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

int	update_game(t_game *game)
{
	if (game->data.game_over == 1)
    {
		game->data.needs_redraw = 1;
        if (game->data.needs_redraw)
        {
            // Clear the screen and draw "Game Over" text with the move count
            mlx_clear_window(game->data.mlx_ptr, game->data.win_ptr);
            mlx_string_put(game->data.mlx_ptr, game->data.win_ptr, 200, 200, 0xFFFFFF, "Game Over!");

            // Convert the move count to string and show the final score
            char *score_str = ft_itoa(game->data.move_count);
            mlx_string_put(game->data.mlx_ptr, game->data.win_ptr, 200, 250, 0xFFFFFF, "Your Score:");
            mlx_string_put(game->data.mlx_ptr, game->data.win_ptr, 320, 250, 0xFFFFFF, score_str);

            free(score_str);
            game->data.needs_redraw = 0;  // Only draw once
        }
        return (0);  // Stop further updates but wait for ESC to exit
    }
	if (game->data.needs_redraw)
	{
		draw_map(game);
		game->data.needs_redraw = 0;
	}
	show_move_count(&game->data);
	return (0);
}

int	game_loop(t_game *game)
{
	mlx_hook(game->data.win_ptr, 2, 1L << 0, handle_keypress, &game->data);
	mlx_hook(game->data.win_ptr, DESTROY_NOTIFY, 0, handle_exit, &game->data);
	mlx_loop_hook(game->data.mlx_ptr, &update_game, game);
	mlx_loop(game->data.mlx_ptr);
	return (0);
}
