/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:12:24 by fgrea             #+#    #+#             */
/*   Updated: 2020/11/28 16:09:29 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = ft_strlen(src);
	if (dstsize == 0)
		return (i);
	while (*src && --dstsize > 0)
		*dst++ = *src++;
	*dst = '\0';
	return (i);
}
