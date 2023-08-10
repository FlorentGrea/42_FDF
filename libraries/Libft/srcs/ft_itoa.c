/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:24:17 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 19:05:04 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char	*fill_str(char *dest, int n, int size)
{
	int	nb;

	nb = n;
	if (n < 0)
		nb = n * -1;
	dest[size--] = (nb % 10) + 48;
	nb /= 10;
	while (nb > 0)
	{
		dest[size--] = (nb % 10) + 48;
		nb /= 10;
	}
	if (size == 0)
		dest[0] = '-';
	return (dest);
}

char	*ft_itoa(int n)
{
	char			*dest;
	int				size;
	unsigned int	nb;

	nb = n;
	if (n < 0)
		nb = n * -1;
	size = 0;
	if (n < 0)
		size = 1;
	nb /= 10;
	while (nb > 0)
	{
		size++;
		nb /= 10;
	}
	dest = (char *)ft_calloc(size + 2, sizeof(char));
	if (!dest)
		return (0);
	dest = fill_str(dest, n, size);
	return (dest);
}
