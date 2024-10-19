/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:39:10 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/19 20:31:51 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

static int	append_to_content(char **file_content, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(*file_content, buffer);
	if (!temp)
	{
		free(*file_content);
		write(2, "Error: Memory allocation failed.\n", 34);
		return (0);
	}
	free(*file_content);
	*file_content = temp;
	return (1);
}

int	open_file(char *name, char **file_content)
{
	int		fd;
	int		ret;
	char	buffer[4096 + 1];

	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (write(2, "Error: Could not open file.\n", 28), 0);

	*file_content = (char *)malloc(1);
	if (!*file_content)
		return (write(2, "Error: Memory allocation failed.\n", 34), 0);

	*file_content[0] = '\0';
	ret = read(fd, buffer, 4096);
	while (ret > 0)
	{
		buffer[ret] = '\0';
		if (!append_to_content(file_content, buffer))
			return (0);
		ret = read(fd, buffer, 4096);
	}
	close(fd);
	return (1);
}

char	*extract_extra_spaces(char *name)
{
	while (*name == ' ' || (*name >= 9 && *name <= 13))
		name++;
	return (name);
}

int	check_correct_map_name(char *name)
{
	if (ft_strncmp(name + ft_strlen(name) - 4, ".ber", 4))
		return (write(2, ".ber not detected\n", 19), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	char	*file_content;
	char	**map;
	t_game	game;

	file_content = NULL;
	map = NULL;
	if (argc == 1)
		return (write(2, "Error: no mapfile included.\n", 29), 1);
	if (argc > 2)
		return (write(2, "Error: too many arguments.\n", 28), 1);
	if (!check_correct_map_name(argv[1]))
		return (1);
	if (!open_file(argv[1], &file_content))
		return (1);
	if (!create_map(file_content, &map))
		return (free(file_content), 1);
	if (!validate_map(map))
		return (deinit(map, file_content, &game), 1);
	ft_printf("Your map is valid. Good job!\n");
	init_graphics(&game.data, map);
	game.sprites = load_sprites(game.data.mlx_ptr);
	game_loop(&game);
	ft_printf("Call deinit.\n");
	deinit(map, file_content, &game);
	return (0);
}
