/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:40:50 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/14 10:53:57 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <fcntl.h>

# define ESC_KEY 53
# define DESTROY_NOTIFY 17
# define UP_KEY 126
# define DOWN_KEY 125
# define LEFT_KEY 123
# define RIGHT_KEY 124

# define TILE_SIZE 64

typedef struct s_point
{
	int		x;
	int		y;
}		t_point;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_point	player_pos;
	t_point	crate_pos;
	char	**map;
}				t_data;

typedef struct s_dimension
{
	int		width;
	int		height;
}		t_dimension;

typedef struct s_sprites
{
	void	*player;
	void	*wall;
	void	*empty;
	void	*collectible;
	void	*exit;
}		t_sprites;

int		validate_map(char **map);
int		create_map(char *file_content, char ***map);
void	init_graphics(char **map);
void	draw_map(char **map, t_data *data);
void	move_player(t_data *data, int dx, int dy);

#endif
