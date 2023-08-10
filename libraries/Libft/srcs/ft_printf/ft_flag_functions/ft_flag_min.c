/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_min.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:09:58 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 18:10:00 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

int	ft_flag_min(t_flags flags, int size)
{
	int	ret;

	ret = flags.min - size;
	while (flags.min-- > size)
		ft_putchar_fd(' ', 1);
	return (ret);
}
