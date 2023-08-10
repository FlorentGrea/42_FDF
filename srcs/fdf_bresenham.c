/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bresenham.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:44:12 by fgrea             #+#    #+#             */
/*   Updated: 2022/05/12 13:19:15 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_calc	fdf_algo_part_1(t_calc c)
{
	if (c.e < 0)
	{
		if (c.interchange == 1)
			c.y += c.s2;
		else
			c.x += c.s1;
		c.e += c.a;
	}
	else
	{
		c.y += c.s2;
		c.x += c.s1;
		c.e += c.b;
	}
	return (c);
}

t_calc	fdf_algo_set(t_calc c, int x2, int y2)
{
	c.dx = ft_abs(x2 - c.x);
	c.dy = ft_abs(y2 - c.y);
	c.s1 = (((x2 - c.x) > 0) * 2) - 1;
	c.s2 = (((y2 - c.y) > 0) * 2) - 1;
	if (c.dy > c.dx)
	{
		c.tmp = c.dx;
		c.dx = c.dy;
		c.dy = c.tmp;
		c.interchange = 1;
	}
	else
		c.interchange = 0;
	c.e = 2 * c.dy - c.dx;
	c.a = 2 * c.dy;
	c.b = 2 * c.dy - 2 * c.dx;
	return (c);
}

int	*fdf_bresenham_algo(t_calc c, int x2, int y2, t_mod mod)
{
	int	i;

	i = c.height_1;
	c = fdf_algo_set(c, x2, y2);
	while (c.dx--)
	{
		if (c.x > 0 && c.x < WIDTH && c.y > 0 && c.y < HEIGHT)
			c.img[c.x + (c.y * WIDTH)] = \
							fdf_get_color(c.height_1 + i, mod);
		c = fdf_algo_part_1(c);
		if (c.height_1 < c.height_2)
			i++;
		if (c.height_1 > c.height_2)
			i--;
	}
	return (c.img);
}

int	*fdf_bresenham(t_calc c, int i, int j, t_mod mod)
{
	int	x1;
	int	y1;

	x1 = mod.middle_x + (i + j - 1) * mod.dist_x;
	c.height_1 = mod.pxl.map[j][i];
	if (i > 0)
	{
		y1 = mod.middle_y + (j + (mod.height - \
					mod.pxl.map[j][i - 1]) - (i - 1)) * mod.dist_y;
		c.height_2 = mod.pxl.map[j][i - 1];
		if (!(c.x < 0 && x1 < 0) || \
				!(c.x > WIDTH && x1 > WIDTH))
			c.img = fdf_bresenham_algo(c, x1, y1, mod);
	}
	if (j > 0)
	{
		y1 = mod.middle_y + ((j - 1) + (mod.height - \
					mod.pxl.map[j - 1][i]) - i) * mod.dist_y;
		c.height_2 = mod.pxl.map[j - 1][i];
		if (!(c.y < 0 && y1 < 0) || \
				!(c.y > HEIGHT && y1 > HEIGHT))
			c.img = fdf_bresenham_algo(c, x1, y1, mod);
	}
	return (c.img);
}
