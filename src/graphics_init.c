/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:12:14 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/11 21:12:03 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

// Function to handle key press events
int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	return (0);
}

// Function to handle window close (cross click)
int	handle_exit(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
	return (0);
}

// Initialize graphics, create window, set event hooks
void	init_graphics(char **map)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
	{
		write(2, "Error: Unable to initialize MiniLibX\n", 37);
		exit(1);
	}
	data.win_ptr = mlx_new_window(data.mlx_ptr, 800, 600, "so_long");
	if (!data.win_ptr)
	{
		write(2, "Error: Unable to create window\n", 31);
		exit(1);
	}
	mlx_hook(data.win_ptr, 2, 1L<<0, handle_keypress, &data);
	mlx_hook(data.win_ptr, DESTROY_NOTIFY, 0, handle_exit, &data);
	draw_map(map, &data);
	mlx_loop(data.mlx_ptr);
}

