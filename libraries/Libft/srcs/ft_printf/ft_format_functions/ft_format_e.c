/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_e.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:11:47 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 18:11:47 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

static int	ft_inf_case(t_printf data, t_flags flags, t_dbl v)
{
	static char	*limits[] = {"nan", "inf", "-inf"};
	int			size;

	size = 0;
	size = ft_strlen(limits[v.pow - 400]);
	if (v.pow - 400 == 1 && (ft_search(data.s, "+") || ft_search(data.s, " ")))
		size++;
	if (flags.nbr > size)
		data.ret += ft_flag_number(flags, size);
	if (flags.zero > size)
	{
		data.ret += flags.zero - size;
		while (flags.zero-- > size)
			ft_putchar_fd(' ', 1);
	}
	if (v.pow - 400 == 1 && ft_search(data.s, "+"))
		ft_putchar_fd('+', 1);
	else if (v.pow - 400 == 1 && ft_search(data.s, " "))
		ft_putchar_fd(' ', 1);
	ft_putstr_fd(limits[v.pow - 400], 1);
	if (flags.min > size)
		data.ret += ft_flag_min(flags, size);
	return (data.ret + size);
}

int	ft_format_e(t_printf data, t_flags flags, va_list ap)
{
	t_dbl		v;

	v = ft_getdbl((double)va_arg(ap, double));
	if (v.pow >= 400)
		return (ft_inf_case(data, flags, v));
	return (ft_dbl_case_e(data, flags, v));
}
