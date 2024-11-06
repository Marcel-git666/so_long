/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:43:33 by mmravec           #+#    #+#             */
/*   Updated: 2024/11/05 21:12:08 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

static void	handle_move_to_empty(t_data *data, int new_x, int new_y)
{
	data->map[data->player_pos.y][data->player_pos.x] = '0';
	data->map[new_y][new_x] = 'P';
	data->player_pos.x = new_x;
	data->player_pos.y = new_y;
	data->move_count++;
	data->needs_redraw = 1;
}

static void	handle_move_crate(t_data *data, int new_x, int new_y)
{
	int		crate_x;
	int		crate_y;

	crate_x = new_x + (new_x - data->player_pos.x);
	crate_y = new_y + (new_y - data->player_pos.y);
	data->map[data->player_pos.y][data->player_pos.x] = '0';
	data->map[new_y][new_x] = 'P';
	data->player_pos.x = new_x;
	data->player_pos.y = new_y;
	if (data->map[crate_y][crate_x] == 'E')
		data->crate_count--;
	else
		data->map[crate_y][crate_x] = 'C';
	data->move_count++;
	data->needs_redraw = 1;
}

static void	handle_exit_condition(t_data *data, int new_x, int new_y)
{
	data->map[data->player_pos.y][data->player_pos.x] = '0';
	data->map[new_y][new_x] = 'P';
	data->player_pos.x = new_x;
	data->player_pos.y = new_y;
	if (data->crate_count == 0)
	{
		ft_printf("Finish the game called.\n");
		data->game_over = 1;
		data->game_won = 1;
		data->needs_redraw = 0;
	}
}

void	move_player(t_data *data, int dx, int dy)
{
	int		new_x;
	int		new_y;

	new_x = data->player_pos.x + dx;
	new_y = data->player_pos.y + dy;
	if (data->map[new_y][new_x] == '0')
		handle_move_to_empty(data, new_x, new_y);
	else if (data->map[new_y][new_x] == 'C'
		&& (data->map[new_y + dy][new_x + dx] == '0'
		|| data->map[new_y + dy][new_x + dx] == 'E'))
		handle_move_crate(data, new_x, new_y);
	else if (data->map[new_y][new_x] == 'E' && data->crate_count == 0)
		handle_exit_condition(data, new_x, new_y);
}
