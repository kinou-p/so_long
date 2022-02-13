/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:42:55 by apommier          #+#    #+#             */
/*   Updated: 2022/02/13 22:26:17 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include "./libft/libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

size_t	ft_strlen_double(char **s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	quit_game(t_data *img)
{
	int	i;

	i = 0;
	mlx_clear_window(img->mlx, img->mlx_win);
	mlx_destroy_window(img->mlx, img->mlx_win);
	mlx_destroy_display(img->mlx);
	if (img->mlx)
		free(img->mlx);
	while (img->map_tab[i])
		free(img->map_tab[i++]);
	free(img->map_tab);
	exit(1);
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

void	print_case(char type, t_data *img, int y, int x)
{
	int	*buffer;
	int	img_width;
	int	img_height;

	if (type == '1')
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/snow_tree.xpm",
				&img_width, &img_height);
	else if (type == 'P')
		buffer = choose_bear(img);
	else if (type == 'C')
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/honey.xpm",
				&img_width, &img_height);
	else if (type == 'E')
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/exit.XPM",
				&img_width, &img_height);
	else
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/back.xpm",
				&img_width, &img_height);
	mlx_put_image_to_window(img->mlx, img->mlx_win, buffer, x * 32, y * 32);
	mlx_destroy_image(img->mlx, buffer);
}

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

void	change_map(t_data *img, int y, int x, char *change)
{
	if (*change == '0' || *change == 'C')
	{
		if (*change == 'C')
			img->item--;
		img->move++;
		ft_putnbr_fd(img->move, 1);
		ft_putchar_fd('\n', 1);
		img->map_tab[y][x] = '0';
		*change = 'P';
	}
	else if (*change == 'E')
	{
		if (img->item <= 0)
		{
			img->move++;
			ft_putnbr_fd(img->move, 1);
			ft_putchar_fd('\n', 1);
			quit_game(img);
		}
	}
}

int	is_good(char **map, int type, t_data *img)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (map[j] && map[j][i] != 'P')
	{
		i = 0;
		while (map[j][i] && map[j][i] != 'P')
			i++;
		if (map[j][i] != 'P')
			j++;
	}
	img->bear = type;
	if (type == 119)
		change_map(img, j, i, &map[j - 1][i]);
	else if (type == 97)
		change_map(img, j, i, &map[j][i - 1]);
	else if (type == 115)
		change_map(img, j, i, &map[j + 1][i]);
	else if (type == 100)
		change_map(img, j, i, &map[j][i + 1]);
	else
		return (0);
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

char	**set_map(char **argv)
{
	char	**map;
	char	*map_line;
	char	*del;
	char	*swap;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	swap = get_next_line(fd);
	while (swap)
	{
		del = map;
		map = ft_strjoin(map, swap);
		free(swap);
		swap = get_next_line(fd);
		free(del);
	}
	return (map);
}

int	main(int argc, char **argv)
{
	t_data	img;
	char	*map;
	int		fd;
	char	*swap;
	char	*del;

	map = 0;
	(void)argc;
	img.bear = 0;
	img.move = 0;
	fd = open(argv[1], O_RDONLY);
	swap = get_next_line(fd);
	while (swap)
	{
		del = map;
		map = ft_strjoin(map, swap);
		free(swap);
		swap = get_next_line(fd);
		free(del);
	}
	img.map_tab = ft_split(map, '\n');
	check_map(img.map_tab);
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, ft_strlen(img.map_tab[0]) * 32,
			ft_strlen_double(img.map_tab) * 32, "Hungry Bear");
	print_map(img.map_tab, &img);
	free(map);
	mlx_hook(img.mlx_win, 2, 1L << 0, &key_press, &img);
	mlx_loop(img.mlx);
}
