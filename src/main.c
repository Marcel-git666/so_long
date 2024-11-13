/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:39:10 by mmravec           #+#    #+#             */
/*   Updated: 2024/11/13 10:24:37 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

int	check_correct_map_name(char *name)
{
	if (ft_strncmp(name + ft_strlen(name) - 4, ".ber", 4))
		return (write(2, "Error\n.ber not detected\n", 24), 0);
	return (1);
}

static int	validate_arguments(int argc, char *name)
{
	if (argc == 1)
		return (write(2, "Error\nNo mapfile included.\n", 27), 0);
	if (argc > 2)
		return (write(2, "Error\nToo many arguments.\n", 26), 0);
	if (!check_correct_map_name(name))
		return (0);
	return (1);
}

static int	initialize_game(t_game **game)
{
	*game = (t_game *)malloc(sizeof(t_game));
	if (!*game)
		return (write(2, "Error\nMemory allocation failed for game.\n", 41), 0);
	(*game)->sprites = NULL;
	(*game)->player_sprites = NULL;
	return (1);
}

int	main(int argc, char **argv)
{
	char	*file_content;
	char	**map;
	t_game	*game;

	file_content = NULL;
	map = NULL;
	if (!initialize_game(&game))
		return (free(game), 1);
	if (!validate_arguments(argc, argv[1]) || !open_file(argv[1],
			&file_content))
		return (free(game), 1);
	if (!create_map(file_content, &map))
		return (free(file_content), free(game), 1);
	if (!validate_map(map))
		return (free_map(map), free(file_content), free(game), 1);
	if (!has_valid_path(map))
		return (free_map(map), free(file_content), free(game), 1);
	game->data.map = map;
	init_graphics(game);
	game->sprites = load_sprites(game->data.mlx_ptr);
	game->player_sprites = load_player_sprites(game->data.mlx_ptr);
	draw_map(game);
	game_loop(game);
	deinit(map, file_content, game);
	return (0);
}
