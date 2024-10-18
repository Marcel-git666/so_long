/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:40:50 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/18 20:19:29 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <fcntl.h>

# define ESC_KEY 53
# define DESTROY_NOTIFY 17
// # ifdef __APPLE__
// #  define UP_KEY 126
// #  define DOWN_KEY 125
// #  define LEFT_KEY 123
// #  define RIGHT_KEY 124
// # elif __linux__
#  define UP_KEY 65362
#  define DOWN_KEY 65364
#  define LEFT_KEY 65361
#  define RIGHT_KEY 65363
// # endif

# define TILE_SIZE 64

typedef struct s_point
{
	int		x;
	int		y;
}		t_point;

typedef struct s_sprites
{
	void	*player;
	void	*wall;
	void	*empty;
	void	*collectible;
	void	*exit;
	void	*free_exit;
	void	*digit_0;
	void	*digit_1;
	void	*digit_2;
}		t_sprites;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_point		player_pos;
	t_point		crate_pos;
	int			move_count;
	char		**map;
	int			crate_count;
	t_sprites	sprites;
}				t_data;

typedef struct s_dimension
{
	int		width;
	int		height;
}		t_dimension;

int		validate_map(char **map);
int		create_map(char *file_content, char ***map);
void	init_graphics(t_data *data, char **map);
int		handle_keypress(int keycode, t_data *data);
int		handle_exit(t_data *data);
void	draw_map(char **map, t_data *data);
void	move_player(t_data *data, int dx, int dy);
void	deinit(char **map, char *file_content);
void	game_loop(t_data *data);
//void	draw_number(t_data *data, int number, int x, int y);

#endif
