//#include <mlx.h>
#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include "./libft/libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
//#include "mlx_int.h"

typedef struct	s_data {
	void	*mlx;
	void	*mlx_win;
	char	**map_tab;
	int		item;
	int		move;
	int		bear;
}				t_data;

void	quit_game(t_data *img)
{
	int	i;
	int j;
	int *image;

	i = 0;
	j = 0;
	printf("quit game\n");
	//image = mlx_new_image(img->mlx, 13 * 32, 10 * 32);
	//mlx_put_image_to_window(img->mlx, img->mlx_win, image, 0, 0)
	mlx_clear_window(img->mlx, img->mlx_win);
	mlx_destroy_window(img->mlx, img->mlx_win);


	mlx_destroy_display(img->mlx);
	if (img->mlx)
		free(img->mlx);
	//if (img->mlx_win)
	//	free(img->mlx_win);	
	while (img->map_tab[i])
		free(img->map_tab[i++]);
	//if (img->map_tab);
	free(img->map_tab);
	exit(1);
}

int *choose_bear(t_data *img)
{
	int *buffer;
	int		img_width;
	int		img_height;
	
	buffer = 0;
	if (img->bear == 119)
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/back_bear.xpm", &img_width, &img_height);
	else if (img->bear == 97)
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/left_bear.xpm", &img_width, &img_height);
	else if (img->bear == 100)
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/right_bear.xpm", &img_width, &img_height);
	else
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/front_bear.xpm", &img_width, &img_height);
	if (buffer == 0)
		return (0);
	return (buffer);
}

void	print_case(char type, t_data *img, int y, int x)
{
	int 	*buffer;
	int		img_width;
	int		img_height;

	if (type == '1')
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/snow_tree.xpm", &img_width, &img_height);
	else if (type == 'P')
		buffer = choose_bear(img);
	else if (type == 'C')
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/honey.xpm", &img_width, &img_height);
	else if (type == 'E')
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/exit.XPM", &img_width, &img_height);
	else
		buffer = mlx_xpm_file_to_image(img->mlx, "./sprite/back.xpm", &img_width, &img_height);
	mlx_put_image_to_window(img->mlx, img->mlx_win, buffer, x * 32, y * 32);
	//free(buffer);
	mlx_destroy_image(img->mlx, buffer);
	//free(buffer);
}

void print_map(char **map, t_data *img)
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

int change_map(t_data *img, int y, int x, char *change)
{
	if (*change == '0' || *change == 'C')
	{
		if (*change == 'C')
			img->item--;
		img->move++;
		printf("%d\n", img->move);
		img->map_tab[y][x] = '0'; 
		*change = 'P';
	}
	else if (*change == 'E')
	{
		img->move++;
		printf("%d\n", img->move);
		if (img->item <= 0)
			quit_game(img);
	}

}

/*void choose_bear(t_data *img, int type)
{
	img->bear = 0; 
	if (type == 119)
		;
	else if (type == 97)
		change_map(img, j, i, &map[j][i - 1]);
	else if (type == 115)
		change_map(img, j, i, &map[j + 1][i]);
	else if (type == 100)
		change_map(img, j, i, &map[j][i + 1]);
}*/

int	is_good(char **map, int type, t_data *img)
{
	int j;
	int i;

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
	return 1;
}

int test(int code, t_data *img)
{
	printf("code = %d\n", code);
	if (code == 65307)
		quit_game(img);
	is_good(img->map_tab, code, img);
	print_map(img->map_tab, img);
}

int	main(int argc, char **argv)
{
	t_data	img;
	char	*map = 0;
	char	**map_tab;
	int		fd = 0;
	char	*swap = 0;
	char	*del;

	img.bear = 0;
	img.move = 0;
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, 13 * 32, 10 * 32, "Hungry Bear");
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
	print_map(img.map_tab, &img);
	free(map);
	mlx_key_hook(img.mlx_win, &test, &img);
	mlx_loop(img.mlx);
	printf("heeeeeeeeeeeeeeerreeeee\n\n\n\n");
}
	
	
	
	
	/*img.img = mlx_xpm_file_to_image(mlx, "./sprite/back.xpm", &img_width, &img_height);
	if (!img.img)
		return 0;
	//img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	/*while (i != 320)
	{
		j = 0;
		while (j != 320)
		{
			mlx_put_image_to_window(mlx, mlx_win, img.img, i, j);
			j += 32;
		}
		i += 32;
	}*/
	//offset = (1920 * line_length + 1080 * (bits_per_pixel / 8));