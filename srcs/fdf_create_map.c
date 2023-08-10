/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:45:23 by fgrea             #+#    #+#             */
/*   Updated: 2022/05/12 13:34:59 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	*fdf_fill_line(char *line, int *new_line, int count)
{
	int	*tmp;
	int	i;

	tmp = new_line;
	i = 0;
	while (count--)
	{
		*tmp++ = ft_atoi(line);
		line = ft_strchr(line, ' ');
		while (line && *line && *line == ' ')
			line++;
	}
	return (new_line);
}

int	*fdf_setup_line(char *line, int *count)
{
	char	*tmp;
	int		*new_line;

	tmp = line;
	*count = 0;
	while (tmp && *tmp++)
	{
		(*count)++;
		tmp = ft_strchr(tmp, ' ');
		while (tmp && *tmp && *tmp == ' ')
			tmp++;
	}
	new_line = calloc(*count, sizeof(int));
	if (!new_line)
		fdf_error(2);
	return (fdf_fill_line(line, new_line, *count));
}

t_pxl	fdf_create_map(char *str, int line_count, t_pxl pxl)
{
	char	*line;
	int		count;
	int		fd;
	int		i;

	i = 0;
	pxl.map = ft_calloc(line_count, sizeof(int *));
	if (!pxl.map)
		fdf_error(2);
	fd = open(str, O_RDONLY);
	while (i < line_count)
	{
		if (get_next_line(fd, &line) < 0)
		{
			while (--i)
				free(pxl.map[i]);
			free(pxl.map);
			fdf_error(1);
		}
		pxl.map[i++] = fdf_setup_line(line, &count);
		pxl.map_line_size = count;
		free(line);
	}
	close(fd);
	return (pxl);
}

t_pxl	fdf_reading(char *str)
{
	t_pxl	pxl;
	char	*tmp;
	int		line_count;
	int		err;
	int		fd;

	line_count = -1;
	err = 1;
	fd = open(str, O_RDONLY);
	while (err > 0)
	{
		tmp = NULL;
		err = get_next_line(fd, &tmp);
		if (err == -1)
			fdf_error(1);
		line_count++;
		free(tmp);
	}
	close(fd);
	pxl.map_line_nbr = line_count;
	return (fdf_create_map(str, line_count, pxl));
}
