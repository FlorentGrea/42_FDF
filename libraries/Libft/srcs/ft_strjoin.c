/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:03:03 by fgrea             #+#    #+#             */
/*   Updated: 2022/05/12 12:53:20 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*dst;
	char	*ret;

	dst = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ret = dst;
	dst = ft_memcpy(dst, s1, ft_strlen(s1));
	dst += ft_strlen(s1);
	dst = ft_memcpy(dst, s2, ft_strlen(s2));
	dst += ft_strlen(s2);
	*dst = '\0';
	return (ret);
}
