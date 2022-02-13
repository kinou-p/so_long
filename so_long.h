/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:30:59 by apommier          #+#    #+#             */
/*   Updated: 2022/02/13 22:12:14 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct	s_data {
	void	*mlx;
	void	*mlx_win;
	char	**map_tab;
	int		item;
	int		move;
	int		bear;
}				t_data;

int check_map(char **map);

#endif