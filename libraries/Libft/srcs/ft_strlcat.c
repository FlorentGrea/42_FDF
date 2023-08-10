/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:20:32 by fgrea             #+#    #+#             */
/*   Updated: 2020/11/28 11:33:10 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	d;
	size_t	s;

	d = ft_strlen(dst);
	s = ft_strlen(src);
	if (d >= dstsize)
		return (s + dstsize);
	i = d;
	while (i < (dstsize - 1) && *src)
		dst[i++] = *src++;
	dst[i] = '\0';
	return (s + d);
}
