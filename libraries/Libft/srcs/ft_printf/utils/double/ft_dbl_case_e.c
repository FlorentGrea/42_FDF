/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbl_case_e.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:14:55 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 18:15:30 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

static int	ft_size(t_printf data, t_flags flags, t_dbl *v)
{
	int	size;

	size = 1;
	if (flags.prec >= 0)
		size += flags.prec;
	else
		size += 6;
	*v = ft_round_dbl(*v, size);
	size += 4;
	if (v->pow > 99 || v->pow < -99)
		size++;
	if (flags.prec != 0 || ft_search(data.s, "#"))
		size++;
	if (v->sign < 0 || ft_search(data.s, "+") || ft_search(data.s, " "))
		size++;
	return (size);
}

static t_printf	ft_flags(t_printf data, t_flags *flags, t_dbl v, int size)
{
	flags->zero -= size;
	if (flags->nbr > size)
		data.ret += ft_flag_number(*flags, size);
	if (v.sign < 0)
		ft_putchar_fd('-', 1);
	else if (ft_search(data.s, "+"))
		ft_flag_plus();
	else if (ft_search(data.s, " "))
		ft_flag_spc();
	if (flags->zero > 0)
		ft_flag_zero(*flags);
	if (flags->zero > 0)
		data.ret += flags->zero;
	ft_putchar_fd(*v.decimal++, 1);
	if (flags->prec > 0 || ft_search(data.s, "#") || flags->prec < 0)
	{
		ft_putchar_fd('.', 1);
		if (flags->prec < 0)
			flags->prec = 6;
		while (*v.decimal && flags->prec-- > 0)
			ft_putchar_fd(*v.decimal++, 1);
		while (flags->prec-- > 0)
			ft_putchar_fd('0', 1);
	}
	return (data);
}

int	ft_dbl_case_e(t_printf data, t_flags flags, t_dbl v)
{
	char	*to_free;
	int		size;
	int		div;

	div = 1;
	size = ft_size(data, flags, &v);
	to_free = v.decimal;
	data = ft_flags(data, &flags, v, size);
	ft_putchar_fd('e', 1);
	if (v.pow < 0)
	{
		v.pow *= -1;
		ft_putchar_fd('-', 1);
	}
	else
		ft_putchar_fd('+', 1);
	if (v.pow < 10)
		ft_putchar_fd('0', 1);
	ft_putnbr_fd(v.pow, 1);
	if (flags.min > size)
		data.ret += ft_flag_min(flags, size);
	free(to_free);
	to_free = NULL;
	v.decimal = NULL;
	return (data.ret + size);
}
