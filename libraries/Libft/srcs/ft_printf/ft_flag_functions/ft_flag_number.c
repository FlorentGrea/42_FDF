/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_number.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:10:07 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 18:10:08 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

int	ft_flag_number(t_flags flags, int size)
{
	int	ret;

	ret = flags.nbr - size;
	while (flags.nbr-- > size)
		ft_putchar_fd(' ', 1);
	return (ret);
}
