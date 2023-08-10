/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:44:51 by fgrea             #+#    #+#             */
/*   Updated: 2020/11/28 15:49:30 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*ret;

	ret = dst;
	if (!dst && !src)
		return (NULL);
	if (dst > src)
		while (len-- > 0)
			*(unsigned char *)(dst + len) = \
							*(unsigned char *)(src + len);
	else
		while (len-- > 0)
			*(unsigned char *)dst++ = *(unsigned char *)src++;
	return (ret);
}
