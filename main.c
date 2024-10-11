/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:39:10 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/11 16:59:35 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "so_long.h"


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
	while ((ret = read(fd, buffer, 4096)) > 0)
	{
		buffer[ret] = '\0';
		*file_content = ft_strjoin(*file_content, buffer);
		if (!*file_content)
			return (write(2, "Error: Memory allocation failed.\n", 34), 0);
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
	size_t		i;

	i = ft_strlen(name);
	if (!((name[i - 4] == '.') && (name[i - 1] == 'r') && (name[i - 2] == 'e')
			&& (name[i - 3] == 'b')))
		return (write(2, ".ber not detected\n", 19), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	char	*file_content;
	char	**map;
	int		i;

	file_content = NULL;
	map = NULL;
	if (argc == 1)
		return (write(2, "Error: no mapfile included.\n", 29), 1);
	if (argc > 2)
		return (write(2, "Error: too many arguments.\n", 28), 1);
	argv[1] = extract_extra_spaces(argv[1]);
	if (!check_correct_map_name(argv[1]))
		return (1);
	if (!open_file(argv[1], &file_content))
		return (1);
	ft_printf("File content:\n%s\n", file_content);
	if (!create_map(file_content, map))
		return (free(file_content), 1);
	i = 0;
	ft_printf("Map has been succesfully created...\n");
	while (map[i])
	{
		ft_printf("Map line %d: %s\n", i, map[i]);
		i++;
	}
	if (!validate_map(map))
	{
		free(file_content);
		i = 0;
		while (map[i])
			free(map[i++]);
		free(map);
		return (1);
	}
	ft_printf("Your map is valid. Good job!\n");
	free(file_content);
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
	return (0);
}
