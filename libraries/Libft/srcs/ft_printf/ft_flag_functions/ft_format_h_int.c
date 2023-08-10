/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_h_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:11:12 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 18:11:13 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

static int	ft_format_int_size(short value, t_printf data, t_flags *flags)
{
	int				size;
	unsigned short	v;

	size = !(value == 0 && flags->prec == 0);
	v = ((!(value < 0) * 2) - 1) * value;
	while ((v / 10) > 0 && size++)
		v /= 10;
	if (flags->prec == 1 && value == 0)
		flags->prec = -1;
	flags->prec -= size;
	flags->zero -= (value < 0 || ft_search(data.s, "+") || \
			ft_search(data.s, " ")) + size;
	if (flags->prec > 0)
		size += flags->prec;
	if (value < 0 || ft_search(data.s, "+") || ft_search(data.s, " "))
		size += 1;
	if (flags->prec < 0 && flags->zero > 0)
		size += flags->zero;
	return (size);
}

static void	ft_putllu_fd(unsigned short nbr, int fd)
{
	if (nbr > 9)
		ft_putllu_fd(nbr / 10, fd);
	ft_putchar_fd(nbr % 10 + '0', fd);
}

int	ft_format_h_int(t_printf data, t_flags flags, va_list ap)
{
	short	v;
	int		size;

	v = (short)va_arg(ap, int);
	size = ft_format_int_size(v, data, &flags);
	if (flags.nbr > size)
		data.ret += ft_flag_number(flags, size);
	if (v < 0)
		ft_putchar_fd('-', 1);
	else if (ft_search(data.s, "+"))
		ft_flag_plus();
	else if (ft_search(data.s, " "))
		ft_flag_spc();
	v *= (!(v < 0) * 2) - 1;
	if (flags.zero > 0 && flags.min == 0 && flags.prec < 0)
		ft_flag_zero(flags);
	if (flags.prec > 0)
		ft_flag_prec(flags);
	if (!(flags.prec == 0 && v == 0))
		ft_putllu_fd(v, 1);
	if (flags.min > size)
		data.ret += ft_flag_min(flags, size);
	return (data.ret + size);
}
