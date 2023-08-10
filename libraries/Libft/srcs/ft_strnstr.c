/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:41:31 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 18:03:52 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (len < ft_strlen(needle))
		return (NULL);
	if (!needle)
		return ((char *)haystack);
	while (*haystack && len-- - ft_strlen(needle) && \
			ft_strncmp(haystack, needle, ft_strlen(needle)))
		haystack++;
	if (ft_strncmp(haystack, needle, ft_strlen(needle)))
		return (NULL);
	return ((char *)haystack);
}
