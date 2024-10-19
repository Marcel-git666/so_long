/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:12:31 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/19 14:24:34 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"


void	game_loop(t_game *game)
{
	mlx_hook(game->data.win_ptr, 2, 1L << 0, handle_keypress, &game->data);
	mlx_hook(game->data.win_ptr, DESTROY_NOTIFY, 0, handle_exit, &game->data);
	draw_map(game->data.map, &game->data, game->sprites);
	show_move_count(&game->data);
	if (!game->data.mlx_ptr || !game->data.win_ptr)
	{
		ft_printf("Error: Invalid MLX pointer or Window pointer\n");
		return;
	}
	mlx_loop(game->data.mlx_ptr);
}

