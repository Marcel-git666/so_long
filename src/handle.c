/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:05:42 by mmravec           #+#    #+#             */
/*   Updated: 2024/11/05 14:04:52 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

static void	process_movement(int keycode, t_data *data)
{
	if (keycode == UP_KEY)
	{
		move_player(data, 0, -1);
		data->last_direction = 'U';
	}
	else if (keycode == DOWN_KEY)
	{
		move_player(data, 0, 1);
		data->last_direction = 'D';
	}
	else if (keycode == LEFT_KEY)
	{
		move_player(data, -1, 0);
		data->last_direction = 'L';
	}
	else if (keycode == RIGHT_KEY)
	{
		move_player(data, 1, 0);
		data->last_direction = 'R';
	}
}

int	handle_keypress(int keycode, t_data *data)
{
	// ft_printf("Key %d is pressed.\n", keycode);
	if (data->game_won)
	{
		mlx_loop_end(data->mlx_ptr);
		return (0);
	}
	if (keycode == ESC_KEY)
	{
		data->game_over = 1;
		mlx_loop_end(data->mlx_ptr);
		return (0);
	}
	if (!data->game_over)
	{
		process_movement(keycode, data);
		data->frame = (data->frame % 6) + 1;
		data->needs_redraw = 1;
	}
	return (0);
}

// Function to handle window close (cross click)
int	handle_exit(t_data *data)
{
	data->game_over = 1;
	mlx_loop_end(data->mlx_ptr);
	return (0);
}
