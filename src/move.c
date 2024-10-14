/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:43:33 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/14 11:31:49 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

void	move_to_empty(t_data *data, int new_x, int new_y)
{
	int		player_x;
	int		player_y;

	player_x = data->player_pos.x;
	player_y = data->player_pos.y;
	data->map[player_y][player_x] = '0';
	data->map[new_y][new_x] = 'P';
	data->player_pos.x = new_x;
	data->player_pos.y = new_y;
}

void	move_crate(t_data *data, int new_x, int new_y)
{
	int		crate_x;
	int		crate_y;

	crate_x = data->crate_pos.x;
	crate_y = data->crate_pos.y;
	data->map[crate_y][crate_x] = 'P';
	data->map[new_y][new_x] = 'C';
	data->crate_pos.x = new_x;
	data->crate_pos.y = new_y;
}

void	move_player(t_data *data, int dx, int dy)
{
	int		player_x;
	int		player_y;
	int		new_x;
	int		new_y;

	player_x = data->player_pos.x;
	player_y = data->player_pos.y;
	ft_printf("Current player position (%d, %d)\n", player_x, player_y);
	new_x = player_x + dx;
	new_y = player_y + dy;
	if (data->map[new_y][new_x] == '0')
	{
		ft_printf("Moving to empty space at (%d, %d)\n", new_x, new_y);
		move_to_empty(data, new_x, new_y);
	}
	else if (data->map[new_y][new_x] == 'C'
		&& (data->map[new_y + dy][new_x + dx] == '0'
		|| data->map[new_y + dy][new_x + dx] == 'E'))
	{
		move_to_empty(data, new_x, new_y);
		move_crate(data, new_x + dx, new_y + dy);
	}
	draw_map(data->map, data);
}
