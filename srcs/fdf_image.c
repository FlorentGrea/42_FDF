/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:48:08 by fgrea             #+#    #+#             */
/*   Updated: 2022/05/12 13:26:06 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	fdf_get_color(int height, t_mod mod)
{
	int	light;
	int	red;
	int	green;
	int	blue;

	height /= 4;
	light = 256;
	red = (200 + ((height > 0) * (height * 2)) + mod.key_color) % 256;
	green = (100 + ((height != 0) * (height * 3)) + mod.key_color) % 256;
	blue = (0 + ((height < 0) * (height * 4)) + mod.key_color) % 256;
	return ((light << 24 & 0xFF000000) | \
			(red << 16 & 0x00FF0000) | \
			(green << 8 & 0x0000FF00) | \
			(blue & 0x000000FF));
}

void	fdf_display_hud(t_pxl pxl)
{
	mlx_string_put(pxl.mlx_ptr, pxl.win_ptr, 10, 10, \
			0x00FFFFFF, "moove with :  arrows");
	mlx_string_put(pxl.mlx_ptr, pxl.win_ptr, 10, 30, \
			0x00FFFFFF, "zoom with :   - or =");
	mlx_string_put(pxl.mlx_ptr, pxl.win_ptr, 10, 50, \
			0x00FFFFFF, "color with :  . or /");
	mlx_string_put(pxl.mlx_ptr, pxl.win_ptr, 10, 70, \
			0x00FFFFFF, "rotate with : wasd");
	mlx_string_put(pxl.mlx_ptr, pxl.win_ptr, 10, 90, \
			0x00FFFFFF, "reset with :  r");
	mlx_string_put(pxl.mlx_ptr, pxl.win_ptr, 10, 110, \
			0x00FFFFFF, "exit with :   escape");
}

int	*fdf_define_img(int *img, t_pxl pxl, t_mod mod)
{
	t_calc	c;
	int		i;
	int		j;

	j = -1;
	c.img = img;
	while (++j < pxl.map_line_nbr)
	{
		i = -1;
		while (++i < pxl.map_line_size)
		{
			c.x = mod.middle_x + (i + j) * mod.dist_x;
			c.y = mod.middle_y + (j + (mod.height - \
				mod.pxl.map[j][i]) - i) * mod.dist_y;
			if (c.x > 0 && c.x < WIDTH && c.y > 0 && c.y < HEIGHT)
				img[c.x + (c.y * WIDTH)] = \
					fdf_get_color(mod.pxl.map[j][i], mod);
			if (i > 0 || j > 0)
				img = fdf_bresenham(c, i, j, mod);
		}
	}
	return (img);
}

void	fdf_create_image(t_pxl pxl, t_mod mod)
{
	void	*img_ptr;
	int		*img;
	int		size_line;
	int		bits_per_pixel;
	int		endian;

	mlx_clear_window(pxl.mlx_ptr, pxl.win_ptr);
	img_ptr = mlx_new_image(pxl.mlx_ptr, WIDTH, HEIGHT);
	img = (int *)mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, \
			&endian);
	img = fdf_define_img(img, pxl, mod);
	mlx_put_image_to_window(pxl.mlx_ptr, pxl.win_ptr, img_ptr, 0, 0);
	fdf_display_hud(pxl);
	free(img);
	img = NULL;
}
