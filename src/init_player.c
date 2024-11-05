/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:34:14 by mmravec           #+#    #+#             */
/*   Updated: 2024/11/05 11:34:36 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

void	set_positions(t_data *data, char cell, int x, int y)
{
	if (cell == 'P')
	{
		data->player_pos.x = x;
		data->player_pos.y = y;
	}
	else if (cell == 'C')
	{
		data->crate_pos.x = x;
		data->crate_pos.y = y;
		data->crate_count++;
	}
}

void	init_player_position(t_data *data, char **map)
{
	int		x;
	int		y;

	data->move_count = 0;
	data->crate_count = 0;
	data->game_over = 0;
	data->game_won = 0;
	data->needs_redraw = 1;
	data->last_direction = 'R';
	data->frame = 1;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			set_positions(data, map[y][x], x, y);
			x++;
		}
		y++;
	}
}
