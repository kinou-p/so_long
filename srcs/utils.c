/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 23:37:02 by apommier          #+#    #+#             */
/*   Updated: 2022/02/15 00:08:44 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(char *error_msg, char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
			free(map[i++]);
	}
	ft_putstr_fd(error_msg, 2);
	exit(1);
}

int	check_map(char **map)
{		
	if (!is_rectangle(map))
		ft_error("Error: The map isn't a rectangle\n", map);
	if (!is_close(map))
		ft_error("Error: The map isn't close\n", map);
	if (!is_player(map))
		ft_error("Error: You need just one player\n", map);
	if (!is_exit(map))
		ft_error("Error: There is no exit\n", map);
	if (!is_item(map))
		ft_error("Error: There is no item\n", map);
	return (1);
}

int	quit_game(t_data *img)
{
	int	i;

	i = 0;
	printf("img = %p\n", img);
	mlx_destroy_window(img->mlx, img->mlx_win);
	mlx_destroy_display(img->mlx);
	if (img->mlx)
		free(img->mlx);
	while (img->map_tab[i])
		free(img->map_tab[i++]);
	free(img->map_tab);
	exit(1);
	return (1);
}

int	key_press(int code, t_data *img)
{
	if (code == 65307)
		quit_game(img);
	is_good(img->map_tab, code, img);
	print_map(img->map_tab, img);
	return (1);
}

int	*choose_bear(t_data *img)
{
	int	*buffer;
	int	img_width;
	int	img_height;

	buffer = 0;
	if (img->bear == 119)
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/back_bear.xpm",
				&img_width, &img_height);
	else if (img->bear == 97)
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/left_bear.xpm",
				&img_width, &img_height);
	else if (img->bear == 100)
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/right_bear.xpm",
				&img_width, &img_height);
	else
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/front_bear.xpm",
				&img_width, &img_height);
	if (buffer == 0)
		return (0);
	return (buffer);
}
