/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:40:50 by mmravec           #+#    #+#             */
/*   Updated: 2024/11/05 20:59:46 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <fcntl.h>

# define DESTROY_NOTIFY 17
# ifdef __APPLE__
#  define ESC_KEY 53
#  define UP_KEY 126
#  define DOWN_KEY 125
#  define LEFT_KEY 123
#  define RIGHT_KEY 124
# elif __linux__
#  define ESC_KEY 65307
#  define UP_KEY 65362
#  define DOWN_KEY 65364
#  define LEFT_KEY 65361
#  define RIGHT_KEY 65363
# endif

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
	int			game_over;
	int			game_won;
	int			needs_redraw;
	char		last_direction;
	int			frame;
}				t_data;

typedef struct s_dimension
{
	int		width;
	int		height;
}		t_dimension;

typedef struct s_player_sprites {
	void	*up_stand;
	void	*up_walk;
	void	*up_walk2;
	void	*down_stand;
	void	*down_walk;
	void	*down_walk2;
	void	*left_stand;
	void	*left_walk;
	void	*right_stand;
	void	*right_walk;
}		t_p_sprites;

typedef struct s_game
{
	t_data		data;
	t_sprites	*sprites;
	t_p_sprites	*player_sprites;
}		t_game;

int			validate_map(char **map);
void		free_map(char **map);
int			create_map(char *file_content, char ***map);
int			open_file(char *name, char **file_content);
void		calculate_map_dimensions(t_data *data, int *width, int *height);
void		init_graphics(t_game *game);
void		init_player_position(t_data *data, char **map);
int			handle_keypress(int keycode, t_data *data);
int			handle_exit(t_data *data);
void		draw_map(t_game *game);
void		move_player(t_data *data, int dx, int dy);
void		deinit(char **map, char *file_content, t_game *game);
int			game_loop(t_game *game);
void		*load_sprite(void *mlx_ptr, char *file_path, t_dimension *dim);
t_sprites	*load_sprites(void *mlx_ptr);
t_p_sprites	*load_player_sprites(void *mlx_ptr);
void		show_move_count(t_data *data);
void		animate_player(t_game *game, char direction, int frame);

#endif
