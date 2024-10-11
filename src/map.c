/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:28:49 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/11 20:01:02 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

int	check_walls(char **map, int i, int len)
{
	if ((i == 0 || !map[i + 1]) && ft_strchr(map[i], '0'))
		return (write(2, "Error: Map not surrounded by walls\n", 35), 0);
	if (map[i][0] != '1' || map[i][len - 1] != '1')
		return (write(2, "Error: Map not surrounded by walls\n", 35), 0);
	return (1);
}

void	count_elements(char **map, int *counts, int i)
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
	int		len;
	int		counts[3];

	i = 0;
	while (i < 3)
		counts[i++] = 0;
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (!check_walls(map, i, len))
			return (0);
		count_elements(map, counts, i);
		i++;
	}
	if (counts[0] != 1 || counts[1] != 1 || counts[2] < 1)
		return (write(2, "Error: Invalid player/exit/collectibles\n", 40), 0);
	return (1);
}

int	create_map(char *file_content, char ***map)
{
	*map = ft_split(file_content, '\n');
	if (!*map)
		return (write(2, "Error creating map from file.\n", 31), 0);
	return (1);
}
