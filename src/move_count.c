/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:29:01 by mmravec           #+#    #+#             */
/*   Updated: 2024/11/05 17:29:37 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"

void	show_move_count(t_data *data)
{
	char	*move_str;
	int		x;
	int		y;
	int		color;

	move_str = ft_itoa(data->move_count);
	if (!move_str)
		return ;
	x = 30;
	y = 40;
	color = 0x8B0000;
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, color, move_str);
	mlx_string_put(data->mlx_ptr, data->win_ptr, x + 1, y, color, move_str);
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y + 1, color, move_str);
	mlx_string_put(data->mlx_ptr, data->win_ptr, x - 1, y, color, move_str);
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y - 1, color, move_str);
	free (move_str);
}
