/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:39:10 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/10 19:44:14 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "so_long.h"

char	*extract_extra_spaces(char *name)
{
	while (*name == ' ' || (*name >= 9 && *name <= 13))
		name++;
	return (name);
}

int	check_correct_map_name(char *name)
{
	int		i;

	i = 0;
	while (name[i])
	{
		if (!ft_isprint(name[i]) || name[i] == ' ' || name[i] == '*'
			|| name[i] == '?')
			return (write(2, "Error in name.\n", 16), 0);
		i++;
	}
	if ((name[i - 4] != '.') || (name[i - 1] != 'r') || (name[i - 2] != 'e')
		|| (name[i - 3] != 'b'))
		return (write(2, ".ber not detected\n", 19), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
		return (write(2, "Error: no mapfile included.\n", 29), 1);
	if (argc > 2)
		return (write(2, "Error: too many arguments.\n", 28), 1);
	argv[1] = extract_extra_spaces(argv[1]);
	if (!check_correct_map_name(argv[1]))
		return (1);
	ft_printf("Your argument is: %s\n", argv[1]);
	return (0);
}
