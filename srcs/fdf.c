/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:08:59 by fgrea             #+#    #+#             */
/*   Updated: 2022/05/12 13:27:43 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

const char	*g_errors[] = {
	"Wrong number of arguments",
	"Error while reading the file",
	"Error while allocating the map",
	"Error while allocating the mod struct"
};

void	fdf_error(int ret)
{
	ft_printf("%s\n", g_errors[ret]);
	exit (0);
}

int	fdf_exit(void)
{
	exit(0);
	return (0);
}

t_mod	*fdf_mod_setup(t_pxl pxl, t_mod *mod)
{
	double	final_sqrt;
	double	dist;
	double	angle_x;
	double	angle_y;
	int		i;

	i = 0;
	while (HEIGHT / 2 - pxl.map_line_size * i > 200)
		i++;
	mod->dist_x = i + 1;
	mod->dist_y = i;
	mod->key_color = 0;
	mod->height = 3;
	dist = mod->dist_x * mod->dist_x + mod->dist_x * mod->dist_x;
	dist = sqrt(dist);
	angle_x = pxl.map_line_size * dist;
	angle_y = pxl.map_line_nbr * dist;
	final_sqrt = sqrt(angle_x * angle_x + angle_y * angle_y);
	mod->middle_x = WIDTH / 2 - final_sqrt / 2;
	mod->middle_y = HEIGHT / 2 - (pxl.map_line_nbr - pxl.map_line_size) / 2;
	return (mod);
}

int	main(int ac, char **av)
{
	t_pxl	pxl;
	t_mod	*mod;

	mod = (t_mod *)malloc(sizeof(t_mod));
	if (!mod)
		fdf_error(3);
	if (ac != 2)
		fdf_error(0);
	pxl = fdf_reading(av[1]);
	mod = fdf_mod_setup(pxl, mod);
	pxl.mlx_ptr = mlx_init();
	mlx_do_key_autorepeaton(pxl.mlx_ptr);
	pxl.win_ptr = mlx_new_window(pxl.mlx_ptr, WIDTH, HEIGHT, "FDF");
	mod->pxl = pxl;
	fdf_create_image(pxl, *mod);
	mlx_hook(pxl.win_ptr, 2, 1L << 0, fdf_key_events, mod);
	mlx_hook(pxl.win_ptr, 17, 0, fdf_exit, mod);
	mlx_loop(pxl.mlx_ptr);
	fdf_exit();
	return (0);
}
