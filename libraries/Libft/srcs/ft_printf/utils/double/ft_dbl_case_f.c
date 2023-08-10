/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbl_case_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:15:35 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 18:28:37 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

int	ft_putflags(t_printf data, t_flags flag, t_dbl v, int size)
{
	flag.zero -= size;
	if (flag.nbr > size)
		data.ret += ft_flag_number(flag, size);
	if (v.sign < 0)
		ft_putchar_fd('-', 1);
	else if (ft_search(data.s, "+"))
		ft_flag_plus();
	else if (ft_search(data.s, " "))
		ft_flag_spc();
	if (flag.zero > 0)
	{
		data.ret += flag.zero;
		ft_flag_zero(flag);
	}
	return (data.ret);
}

int	ft_posexp_f(t_printf data, t_flags flag, t_dbl v, int size)
{
	char	*freed;

	size += flag.prec;
	v = ft_round_dbl(v, size);
	freed = v.decimal;
	size += v.sign < 0 || ft_search(data.s, "+") || ft_search(data.s, " ");
	size += flag.prec != 0 || ft_search(data.s, "#");
	data.ret = ft_putflags(data, flag, v, size);
	while (v.pow-- > -1)
		if (*v.decimal)
			ft_putchar_fd(*v.decimal++, 1);
		else
			ft_putchar_fd('0', 1);
	if (ft_search(data.s, "#") || flag.prec > 0)
		ft_putchar_fd('.', 1);
	while (flag.prec--)
		if (*v.decimal)
			ft_putchar_fd(*v.decimal++, 1);
		else
			ft_putchar_fd('0', 1);
	while (size < flag.min && size++)
		ft_putchar_fd(' ', 1);
	free(freed);
	freed = NULL;
	return (data.ret + size);
}

int	ft_negexp_f2(t_printf data, t_flags flag, t_dbl v, int size)
{
	if ((flag.prec == 0 && ft_search(data.s, "#")) || flag.prec != 0)
	{
		data.ret++;
		ft_putchar_fd('.', 1);
		while (++v.pow < 0 && size-- && data.ret++)
			ft_putchar_fd('0', 1);
		while (size-- > 0 && data.ret++)
			if (*v.decimal && flag.min--)
				ft_putchar_fd(*v.decimal++, 1);
			else if (1 || flag.min--)
				ft_putchar_fd('0', 1);
	}
	while (--flag.min > 0 && data.ret++)
		ft_putchar_fd(' ', 1);
	return (data.ret);
}

int	ft_negexp_f(t_printf data, t_flags flag, t_dbl v, int size)
{
	char	*freed;

	data.ret++;
	flag.min += v.pow;
	flag.min -= v.sign < 0 || ft_search(data.s, "+") || ft_search(data.s, " ");
	data.ret += v.sign < 0 || ft_search(data.s, "+") || ft_search(data.s, " ");
	if (flag.prec + (v.pow + 1) >= 0)
		v = ft_round_dbl(v, flag.prec + (v.pow + 1));
	size = flag.prec;
	freed = v.decimal;
	if (v.pow == 0)
		return (ft_posexp_f(data, flag, v, v.pow + 1));
	data.ret = ft_putflags(data, flag, v, size + (v.sign < 0 || \
				ft_search(data.s, "+") || ft_search(data.s, " ")) + 1 \
			+ (flag.prec != 0 || (flag.prec == 0 && !ft_search(data.s, "#"))));
	ft_putchar_fd('0', 1);
	data.ret = ft_negexp_f2(data, flag, v, size);
	free(freed);
	freed = NULL;
	v.decimal = NULL;
	return (data.ret);
}

int	ft_dbl_case_f(t_printf data, t_flags flag, t_dbl v)
{
	int		size;

	size = v.pow + 1;
	if (flag.prec == -1)
		flag.prec = 6;
	if (v.pow >= 0)
		return (ft_posexp_f(data, flag, v, size));
	else
		return (ft_negexp_f(data, flag, v, size));
}
