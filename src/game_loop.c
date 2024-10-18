/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:12:31 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/18 20:33:53 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "so_long.h"
#include "libft.h"


void	game_loop(t_data *data)
{
	t_sprites sprites = load_sprites(data->mlx_ptr);
	mlx_hook(data->win_ptr, 2, 1L << 0, handle_keypress, data);
	mlx_hook(data->win_ptr, DESTROY_NOTIFY, 0, handle_exit, data);
	draw_map(data->map, data, sprites);
	if (!data->mlx_ptr || !data->win_ptr)
	{
		ft_printf("Error: Invalid MLX pointer or Window pointer\n");
		return ;
	}
	mlx_loop(data->mlx_ptr);
}

