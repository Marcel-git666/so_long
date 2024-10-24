/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:43:33 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/24 20:46:39 by mmravec          ###   ########.fr       */
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
	ft_printf("Player has moved..\n");
}

void	move_crate(t_data *data, int new_x, int new_y)
{
	if (data->map[new_y][new_x] == 'E')
		data->crate_count--;
	else
		data->map[new_y][new_x] = 'C';
}

void	show_move_count(t_data *data)
{
	char	*move_str;

	move_str = ft_itoa(data->move_count);
	if (!move_str)
		return ;
	mlx_string_put(data->mlx_ptr, data->win_ptr, 30, 40, 0x8B0000, move_str);
	free(move_str);
}

void	finish_the_game(t_data *data)
{
	ft_printf("Finish the game called.\n");
	data->game_over = 1;
	data->game_won = 1;
	data->needs_redraw = 1;
}

void	move_player(t_data *data, int dx, int dy)
{
	int		new_x;
	int		new_y;

	new_x = data->player_pos.x + dx;
	new_y = data->player_pos.y + dy;
	if (data->map[new_y][new_x] == '0')
	{
		move_to_empty(data, new_x, new_y);
		data->move_count++;
		data->needs_redraw = 1;
	}
	else if (data->map[new_y][new_x] == 'C'
		&& (data->map[new_y + dy][new_x + dx] == '0'
		|| data->map[new_y + dy][new_x + dx] == 'E'))
	{
		move_to_empty(data, new_x, new_y);
		move_crate(data, new_x + dx, new_y + dy);
		data->move_count++;
		data->needs_redraw = 1;
	}
	if (data->map[new_y][new_x] == 'E' && data->crate_count == 0)
	{
		move_to_empty(data, new_x, new_y);
		finish_the_game(data);
		data->needs_redraw = 0;
	}
}
