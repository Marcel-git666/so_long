/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:06:55 by mmravec           #+#    #+#             */
/*   Updated: 2024/11/05 14:07:17 by mmravec          ###   ########.fr       */
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
