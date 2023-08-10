/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:18:51 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 17:52:11 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*r1;
	unsigned char	*r2;

	r1 = (unsigned char *)s1;
	r2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	if (*r1 == *r2 && n > 1)
		ft_memcmp(++r1, ++r2, --n);
	return (*r1 - *r2);
}
