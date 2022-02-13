/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 22:26:34 by apommier          #+#    #+#             */
/*   Updated: 2022/02/13 23:47:44 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_player(char **map)
{
	int	i;
	int	j;
	int	player;

	player = 0;
	i = 0;
	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i++])
		{
			if (map[j][i] == 'P')
				player++;
		}
		j++;
	}
	if (player == 1)
		return (1);
	return (0);
}

int	is_exit(char **map)
{
	int	i;
	int	j;
	int	exit;

	exit = 0;
	i = 0;
	j = 0;
	while (map[j])
	{
		i = 1;
		while (map[j][i])
		{
			if (map[j][i++] == 'E')
				exit++;
		}
		j++;
	}
	if (exit > 0)
		return (1);
	return (0);
}

int	is_item(char **map)
{
	int	i;
	int	j;
	int	item;

	item = 0;
	i = 0;
	j = 0;
	while (map[j])
	{
		i = 1;
		while (map[j][i])
		{
			if (map[j][i++] == 'E')
				item++;
		}
		j++;
	}
	return (item);
}

int	is_rectangle(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[j])
	{
		i = 1;
		while (map[j][i])
		{
			if (map[j][i] != '0' && map[j][i] != '1' && map[j][i] != 'P'
				&& map[j][i] != 'E' && map[j][i] != 'C')
				return (0);
			i++;
		}
		j++;
	}
	j = 0;
	while (map[j + 1])
	{
		if (ft_strlen(map[j]) != ft_strlen(map[j + 1]))
			return (0);
		j++;
	}
	return (1);
}

int	is_close(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[j][i])
	{
		if (map[j][i++] != '1')
			return (0);
	}
	while (map[j])
	{
		if (map[j][0] != '1' || map[j][ft_strlen(map[j]) - 1] != '1')
			return (0);
		j++;
	}
	i = 0;
	while (map[j - 1][i])
	{
		if (map[j - 1][i++] != '1')
			return (0);
	}
	return (1);
}
