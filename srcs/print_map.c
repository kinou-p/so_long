/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 23:39:18 by apommier          #+#    #+#             */
/*   Updated: 2022/02/14 00:42:06 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_map(char **map, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	img->item = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			print_case(map[j][i], img, j, i);
			if (map[j][i] == 'C')
				img->item++;
			i++;
		}
		j++;
	}
}

void	free_double(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
		free(to_free[i++]);
}

void	check_arg(int argc, char **argv)
{
	int	i;
	int	fd;

	fd = 0;
	i = 0;
	if (argc != 2)
		ft_error("Error: Bad number of arguments\n", 0);
	while (argv[1] && argv[1][i] != '.')
		i++;
	if (argv[1][i] == '.' && !ft_strcmp(&argv[1][i], ".ber"))
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			ft_error("Error: The map file doesn't exist\n", 0);
		close(fd);
	}
	else
		ft_error("Error: Bad file type\n", 0);
}
