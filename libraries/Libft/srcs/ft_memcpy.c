/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:34:45 by fgrea             #+#    #+#             */
/*   Updated: 2022/05/12 12:58:18 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*ret;

	if (!src && !dst)
		return (NULL);
	ret = dst;
	while (n-- > 0)
		*(unsigned char *)dst++ = *(unsigned char *)src++;
	return (ret);
}
