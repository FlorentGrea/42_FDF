/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:52:54 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 17:54:35 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

unsigned int	check(char *str)
{
	unsigned int	i;

	while (*str)
	{
		i = 1;
		if (*str == '-' || *str == '+')
			return (1);
		while (str[i])
			if (*str == str[i++])
				return (1);
		str++;
	}
	return (0);
}

void	ft_putnbr_base_fd(int nbr, char *base, int fd)
{
	unsigned int	s;
	unsigned int	n;

	s = ft_strlen(base);
	if (s < 2 || check(base))
		return ;
	if (nbr < 0)
		write(1, "-", 1);
	n = nbr;
	if (nbr < 0)
		n = nbr * -1;
	if (n > s - 1)
		ft_putnbr_base_fd(n / s, base, fd);
	write(fd, &base[n % s], 1);
}
