/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:05:54 by fgrea             #+#    #+#             */
/*   Updated: 2020/11/28 12:35:25 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;

	ret = NULL;
	while (*s)
		if (*s++ == (char)c)
			ret = ((char *)s - 1);
	if (*s == (char)c)
		ret = (char *)s;
	return (ret);
}
