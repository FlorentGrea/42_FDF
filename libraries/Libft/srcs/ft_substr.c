/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:49:47 by fgrea             #+#    #+#             */
/*   Updated: 2022/05/12 13:15:38 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ret;
	char	*dst;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (len == 0 || start >= ft_strlen(s))
		dst = (char *)malloc(1 * sizeof(char));
	else
		dst = (char *)malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ret = dst;
	if (start < ft_strlen(s))
		while (s[start] && len--)
			*dst++ = s[start++];
	*dst = '\0';
	return (ret);
}
