/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:28:49 by mmravec           #+#    #+#             */
/*   Updated: 2024/11/12 11:39:45 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

static int	check_walls(char **map, int i, int len)
{
	if ((i == 0 || !map[i + 1]) && ft_strchr(map[i], '0'))
		return (write(2, "Error\nMap not surrounded by walls\n", 34), 0);
	if (map[i][0] != '1' || map[i][len - 1] != '1')
		return (write(2, "Error\nMap not surrounded by walls\n", 34), 0);
	return (1);
}

static void	count_elements(char **map, int *counts, int i)
{
	int		j;

	j = 0;
	while (map[i][j])
	{
		if (map[i][j] == 'P')
			counts[0]++;
		else if (map[i][j] == 'E')
			counts[1]++;
		else if (map[i][j] == 'C')
			counts[2]++;
		j++;
	}
}

int	validate_map(char **map)
{
	int		i;
	size_t	len;
	int		counts[3];

	i = 0;
	while (i < 3)
		counts[i++] = 0;
	i = 0;
	len = ft_strlen(map[0]);
	while (map[i])
	{
		if (ft_strlen(map[i]) != len)
			return (write(2, "Error\nMap is not rectangular.\n", 30), 0);
		if (!check_walls(map, i, len))
			return (0);
		count_elements(map, counts, i);
		i++;
	}
	if (counts[0] != 1 || counts[1] != 1 || counts[2] < 1)
		return (write(2, "Error\nInvalid player/exit/collectibles\n", 39), 0);
	return (1);
}

static int	has_double_newlines(const char *file_content)
{
	if (*file_content == '\n')
	{
		write(2, "Error\nMap contains extra newlines.\n", 35);
		return (1);
	}
	while (*file_content)
	{
		if (*file_content == '\n' && *(file_content + 1) == '\n')
		{
			write(2, "Error\nMap contains consecutive newlines.\n", 41);
			return (1);
		}
		file_content++;
	}
	return (0);
}

int	create_map(char *file_content, char ***map)
{
	if (has_double_newlines(file_content))
		return (0);
	*map = ft_split(file_content, '\n');
	if (!*map)
		return (write(2, "Error\nError creating map from file.\n", 36), 0);
	return (1);
}
