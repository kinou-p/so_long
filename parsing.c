/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.4map.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: map0map/0map/13 16:map1:43 by apommier          #+#    #+#             */
/*   Updated: map0map/0map/13 map1:map4:44 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"
#include "./libft/libft.h"
#include <stdio.h>


int is_player(char **map)
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

int is_exit(char **map)
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

int is_item(char **map)
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

int is_rectangle(char **map)
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
			if (map[j][i] != '0' && map[j][i] != '1' && map[j][i] != 'P' && map[j][i] != 'E' && map[j][i] != 'C')
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

void ft_error(char *error_msg, char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	ft_putstr_fd(error_msg, 2);
	exit(1);
}

int check_map(char **map)
{
	if (!is_player(map))
		ft_error("You need just one player\n", map);
	if (!is_exit(map))
		ft_error("There is no exit\n", map);
	if (!is_close(map))
		ft_error("The map isn't close\n", map);
	if (!is_item(map))
		ft_error("There is no item\n", map);
	if (!is_rectangle(map))
		ft_error("The map isn't a rectangle\n", map);
	return (1);
}