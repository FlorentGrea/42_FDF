/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:49:00 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 15:53:11 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_mod	*fdf_center_zoom(t_mod *mod)
{
	double	final_sqrt;
	double	dist;
	double	angle_x;
	double	angle_y;

	dist = mod->dist_x * mod->dist_x + mod->dist_x * mod->dist_x;
	dist = sqrt(dist);
	angle_x = mod->pxl.map_line_size * dist;
	angle_y = mod->pxl.map_line_nbr * dist;
	final_sqrt = sqrt(angle_x * angle_x + angle_y * angle_y);
	mod->middle_x = WIDTH / 2 - final_sqrt / 2;
	mod->middle_y = HEIGHT / 2 - \
			(mod->pxl.map_line_nbr - mod->pxl.map_line_size) / 2;
	if (mod->dist_x < 0 || mod->dist_y < 0)
		mod->middle_x = WIDTH + mod->middle_x * -1;
	return (mod);
}

t_mod	*fdf_zoom(int key, t_mod *mod)
{
	if (key == 24)
	{
		mod->dist_x += 1;
		mod->dist_y += 1;
		if (mod->dist_x == 0 || mod->dist_y == 0)
		{
			mod->dist_x = 2;
			mod->dist_y = 1;
		}
	}
	if (key == 27)
	{
		mod->dist_x -= 1;
		mod->dist_y -= 1;
		if (mod->dist_x == 0 || mod->dist_y == 0)
		{
			mod->dist_x = -2;
			mod->dist_y = -1;
		}
	}
	return (fdf_center_zoom(mod));
}

t_mod	*fdf_moove(int key, t_mod *mod)
{
	if (key == 126)
		mod->middle_y -= 16;
	if (key == 125)
		mod->middle_y += 16;
	if (key == 123)
		mod->middle_x -= 16;
	if (key == 124)
		mod->middle_x += 16;
	return (mod);
}

t_mod	*fdf_rotate(int key, t_mod *mod)
{
	if (key == 13)
		mod->dist_y++;
	if (key == 1)
		mod->dist_y--;
	if (key == 0)
		mod->dist_x++;
	if (key == 2)
		mod->dist_x--;
	return (mod);
}

int	fdf_key_events(int key, t_mod *mod)
{
	if (key == 126 || key == 125 || key == 123 || key == 124)
		mod = fdf_moove(key, mod);
	if (key == 27 || key == 24)
		mod = fdf_zoom(key, mod);
	if (key == 13 || key == 1 || key == 0 || key == 2)
		mod = fdf_rotate(key, mod);
	if (key == 53)
		fdf_exit();
	if (key == 44)
		mod->key_color++;
	if (key == 47)
		mod->key_color--;
	if (key == 15)
		mod = fdf_mod_setup(mod->pxl, mod);
	fdf_create_image(mod->pxl, *mod);
	return (0);
}
