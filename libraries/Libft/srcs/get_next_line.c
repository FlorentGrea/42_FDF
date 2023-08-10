/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:06:28 by fgrea             #+#    #+#             */
/*   Updated: 2022/05/12 13:26:14 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	la_norme_cette_sale_grande_tante(int fd, char **r, char **eol)
{
	char		buf[BUFFER_SIZE + 1];
	ssize_t		read_ret;
	char		*tmp;

	read_ret = -2;
	*eol = ft_memchr(*r, '\n', ft_strlen(*r));
	while (read_ret != 0 && !*eol)
	{
		read_ret = read(fd, buf, BUFFER_SIZE);
		if (read_ret < 0)
			return (-1);
		buf[read_ret] = 0;
		tmp = ft_strjoin(*r, buf);
		free(*r);
		*r = tmp;
		if (!*r)
			return (-1);
		*eol = ft_memchr(*r, '\n', ft_strlen(*r));
	}
	return (read_ret);
}

int	get_next_line(int fd, char **line)
{
	static char	*r;
	ssize_t		read_ret;
	char		*tmp;
	char		*eol;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	read_ret = la_norme_cette_sale_grande_tante(fd, &r, &eol);
	if (read_ret == -1)
		return (-1);
	if (!eol)
	{
		*line = ft_substr(r, 0, ft_strlen(r));
		free(r);
		r = NULL;
		return (0);
	}
	*line = ft_substr(r, 0, eol - r);
	tmp = ft_substr(r, (eol - r) + 1, ft_strlen(r) - (eol - r));
	free(r);
	r = NULL;
	r = tmp;
	return (1);
}
