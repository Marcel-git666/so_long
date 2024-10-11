/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:40:50 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/11 21:14:05 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <fcntl.h>
# define ESC_KEY 53
# define DESTROY_NOTIFY 17
# define TILE_SIZE 16

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_data;

int		validate_map(char **map);
int		create_map(char *file_content, char ***map);
void	init_graphics(char **map);
void	draw_map(char **map, t_data *data);

#endif
