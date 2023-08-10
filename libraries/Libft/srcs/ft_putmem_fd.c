/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmem_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:52:22 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 17:52:43 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putmem_fd(unsigned long int pt_addr, int fd)
{
	if (pt_addr > 15)
		ft_putmem_fd(pt_addr >> 4, fd);
	ft_putnbr_base_fd(pt_addr % 16, "0123456789abcdef", fd);
}
