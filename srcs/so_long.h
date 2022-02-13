/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:30:59 by apommier          #+#    #+#             */
/*   Updated: 2022/02/14 00:37:07 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_data {
	void	*mlx;
	void	*mlx_win;
	char	**map_tab;
	int		item;
	int		move;
	int		bear;
}				t_data;

//parsing functions
int		check_map(char **map);
int		is_player(char **map);
int		is_exit(char **map);
int		is_item(char **map);
int		is_rectangle(char **map);
int		is_close(char **map);

//print map
void	print_map(char **map, t_data *img);

//free double pointer
void	free_double(char **to_free);

//check arguments and if map file is correct
void	check_arg(int argc, char **argv);

//utils
void	ft_error(char *error_msg, char **map);
int		check_map(char **map);
void	quit_game(t_data *img);
int		key_press(int code, t_data *img);
int		*choose_bear(t_data *img);

//main functions
void	print_case(char type, t_data *img, int y, int x);
void	change_map(t_data *img, int y, int x, char *change);
int		is_good(char **map, int type, t_data *img);
char	**set_map(char **argv);
int		main(int argc, char **argv);

#endif