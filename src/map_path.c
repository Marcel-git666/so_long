/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:45:42 by mmravec           #+#    #+#             */
/*   Updated: 2024/11/12 20:57:51 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

t_point	find_player_position(char **map)
{
	t_point		pos;
	int			i;
	int			j;

	i = 0;
	pos.x = -1;
	pos.y = -1;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				pos.x = j;
				pos.y = i;
				return (pos);
			}
			j++;
		}
		i++;
	}
	return (pos);
}

t_point	get_map_size(char **map)
{
	t_point	size;

	size.x = 0;
	size.y = 0;
	while (map[size.y])
		size.y++;
	size.x = ft_strlen(map[0]);
	return (size);
}

char	**copy_map(char **map, t_point size)
{
	char	**map_cpy;
	int		i;

	map_cpy = malloc(sizeof(char *) * (size.y + 1));
	if (!map_cpy)
		return (NULL);
	i = 0;
	while (i < size.y)
	{
		map_cpy[i] = ft_strdup(map[i]);
		if (!map_cpy[i])
		{
			free_map(map_cpy);
			return (NULL);
		}
		i++;
	}
	map_cpy[size.y] = NULL;
	return (map_cpy);
}

int	all_collectibles_and_exit_reachable(char **map, t_point size)
{
	int		i;
	int		j;

	i = 0;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			if (map[i][j] == 'C')
				return (0);
			if (map[i][j] == 'E')
			{
				if (!((i > 0 && map[i - 1][j] == 'F')
					|| (i < size.y - 1 && map[i + 1][j] == 'F')
					|| (j > 0 && map[i][j - 1] == 'F')
					|| (j < size.x - 1 && map[i][j + 1] == 'F')))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	has_valid_path(char **map)
{
	t_point	player_pos;
	t_point	map_size;
	char	**map_cpy;

	player_pos = find_player_position(map);
	if (player_pos.x == -1 || player_pos.y == -1)
		return (write(2, "Error\nPlayer position not found\n", 32), 0);
	map_size = get_map_size(map);
	map_cpy = copy_map(map, map_size);
	if (!map_cpy)
		return (0);
	flood_fill(map_cpy, map_size, player_pos);
	ft_printf("After flood fill:\n");
	print_map(map_cpy);
	if (!all_collectibles_and_exit_reachable(map_cpy, map_size))
	{
		free_map(map_cpy);
		return (write(2, "Error\nMap path not found\n", 25), 0);
	}
	free_map(map_cpy);
	return (1);
}
