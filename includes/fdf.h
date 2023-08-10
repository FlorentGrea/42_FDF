/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:36:12 by fgrea             #+#    #+#             */
/*   Updated: 2022/05/12 12:51:08 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <libft.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# ifndef HEIGHT
#  define HEIGHT 720
# endif

# ifndef WIDTH
#  define WIDTH 1280
# endif

typedef struct s_pxl
{
	int		**map;
	int		map_line_nbr;
	int		map_line_size;

	void	*mlx_ptr;
	void	*win_ptr;
}	t_pxl;

typedef struct s_mod
{
	int		dist_x;
	int		dist_y;

	int		middle_x;
	int		middle_y;
	int		key_color;
	int		height;
	t_pxl	pxl;
}	t_mod;

typedef struct s_calc
{
	int	*img;

	int	x;
	int	y;

	int	height_1;
	int	height_2;

	int	dx;
	int	dy;
	int	e;
	int	interchange;
	int	tmp;
	int	a;
	int	b;
	int	s1;
	int	s2;
}	t_calc;

void	fdf_error(int ret);

int		fdf_exit(void);

t_pxl	fdf_reading(char *str);

t_mod	*fdf_mod_setup(t_pxl pxl, t_mod *mod);

void	fdf_create_image(t_pxl pxl, t_mod mod);

int		fdf_get_color(int height, t_mod mod);

int		*fdf_bresenham(t_calc c, int i, int j, t_mod mod);

int		fdf_key_events(int key, t_mod *mod);

#endif
