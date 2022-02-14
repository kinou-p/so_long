/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:42:55 by apommier          #+#    #+#             */
/*   Updated: 2022/02/14 23:49:53 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

char	**set_map(char **argv)
{
	char	**map_tab;
	char	*map;
	char	*del;
	char	*swap;
	int		fd;

	map = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error("Error: Open call fail\n", 0);
	swap = get_next_line(fd);
	while (swap)
	{
		del = map;
		map = ft_strjoin(map, swap);
		free(swap);
		swap = get_next_line(fd);
		free(del);
	}
	close(fd);
	map_tab = ft_split(map, '\n');
	free(map);
	if (!map_tab)
		ft_error("Error: Map file is empty\n", 0);
	return (map_tab);
}

int	button_press(int code, t_data *img)
{
	int	i;


	(void)code;
	printf("img in buttom = %p\n", img);
	printf("move = %d\n", img->move);
	//printf("img->mlx = %p\n", img->mlx);
	i = 0;
	mlx_destroy_window(img->mlx, img->mlx_win);
	mlx_destroy_display(img->mlx);
	if (img->mlx)
		free(img->mlx);
	while (img->map_tab[i])
		free(img->map_tab[i++]);
	free(img->map_tab);
	//quit_game(img);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_data	img;
	int		height;

	height = 0;
	(void)argc;
	check_arg(argc, argv);
	img.bear = 0;
	img.move = 0;
	img.map_tab = set_map(argv);
	while (img.map_tab[height])
		height++;
	check_map(img.map_tab);
	img.mlx = mlx_init();
	if (!img.mlx)
		ft_error("Error: mlx_init fail", img.map_tab);
	img.mlx_win = mlx_new_window(img.mlx, ft_strlen(img.map_tab[0]) * 32,
			height * 32, "Hungry Bear");
	print_map(img.map_tab, &img);
	printf("img in main= %p\n", &img);
	//mlx_hook(img.mlx_win, DestroyNotify, NoEventMask, &button_press, &img);
	
	mlx_hook(img.mlx_win, 2, 1L << 0, &key_press, &img);
	mlx_hook(img.mlx_win, 33, 1L << 17, &button_press, &img);
	//mlx_key_hook(img.mlx_win, &key_press, &img);
	mlx_loop(img.mlx);
}
