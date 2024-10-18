/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:43:33 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/18 16:35:51 by mmravec          ###   ########.fr       */
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
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		"sprites/wall.xpm", 0, 0);
	mlx_string_put(data->mlx_ptr, data->win_ptr, 10, 10, 0xFFFFFF, move_str);
	free(move_str);
}

void finish_the_game(t_data *data)
{
    // Clear the screen and draw "Game Over" text with the move count
    mlx_clear_window(data->mlx_ptr, data->win_ptr);

    // Show "Game Over" and the final score
    mlx_string_put(data->mlx_ptr, data->win_ptr, 200, 200, 0xFFFFFF, "Game Over!");

    // Convert the move count to string and show the final score
    char *score_str = ft_itoa(data->move_count);
    mlx_string_put(data->mlx_ptr, data->win_ptr, 200, 250, 0xFFFFFF, "Your Score:");
    mlx_string_put(data->mlx_ptr, data->win_ptr, 320, 250, 0xFFFFFF, score_str);

    // Free the score string
    free(score_str);

    // Now keep the game running, waiting for ESC or window close
    mlx_hook(data->win_ptr, 2, 1L << 0, handle_keypress, data);  // Hook for keypress events
    mlx_hook(data->win_ptr, DESTROY_NOTIFY, 0, handle_exit, data);  // Hook for window close

    // Exit the loop only when ESC is pressed or window is closed
    mlx_loop(data->mlx_ptr);
}

void	move_player(t_data *data, int dx, int dy)
{
	int		player_x;
	int		player_y;
	int		new_x;
	int		new_y;

	player_x = data->player_pos.x;
	player_y = data->player_pos.y;
	new_x = player_x + dx;
	new_y = player_y + dy;
	if (data->map[new_y][new_x] == '0')
	{
		move_to_empty(data, new_x, new_y);
		data->move_count++;
	}
	else if (data->map[new_y][new_x] == 'C'
		&& (data->map[new_y + dy][new_x + dx] == '0'
		|| data->map[new_y + dy][new_x + dx] == 'E'))
	{
		move_to_empty(data, new_x, new_y);
		move_crate(data, new_x + dx, new_y + dy);
		data->move_count++;
	}
	if (data->map[new_y][new_x] == 'E' && data->crate_count == 0)
	{
		move_to_empty(data, new_x, new_y);
		finish_the_game(data);
	}
	ft_printf("Redrawing map....\n");
	draw_map(data->map, data);
	// draw_number(data, 210, 0, 0);
	show_move_count(data);
}
