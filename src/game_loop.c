/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:12:31 by mmravec           #+#    #+#             */
/*   Updated: 2024/11/05 20:37:38 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

static void	display_game_over(t_data *data)
{
	t_dimension	dim;
	char		*score_str;
	int			center_x;
	int			center_y;

	calculate_map_dimensions(data, &dim.width, &dim.height);
	center_x = dim.width / 2;
	center_y = dim.height / 2;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		center_x - 50, center_y - 60, 0xFFFFFF, "Game Over!");
	score_str = ft_itoa(data->move_count);
	if (score_str)
	{
		mlx_string_put(data->mlx_ptr, data->win_ptr, center_x - 80,
			center_y, 0xFFFFFF, "Your Score:");
		mlx_string_put(data->mlx_ptr, data->win_ptr, center_x + 40,
			center_y, 0xFFFFFF, score_str);
		free(score_str);
	}
	mlx_string_put(data->mlx_ptr, data->win_ptr, center_x - 120,
		center_y + 70, 0xFFFFFF, "Press any key to exit the game ...");
	data->needs_redraw = 0;
}

int	update_game(t_game *game)
{
	if (game->data.game_over == 1)
	{
		game->data.needs_redraw = 1;
		if (game->data.needs_redraw)
			display_game_over(&game->data);
		return (0);
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
