/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getdbl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:19:26 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 18:19:27 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

t_dbl	ft_inf_cases(t_dbl dbl, unsigned long long parsed_dbl)
{
	int	i;

	i = 11;
	dbl.pow = 401;
	dbl.decimal = NULL;
	if (dbl.sign == -1)
		dbl.pow = 402;
	while (++i < 64)
		if ((parsed_dbl >> (63 - i) & 1))
			dbl.pow = 400;
	return (dbl);
}

t_dbl	ft_getdbl(double d)
{
	t_dbl				dbl;
	unsigned long long	parsed_dbl;
	int					exp;
	int					base;
	int					i;

	i = 12;
	exp = 0;
	base = 1;
	ft_memcpy(&parsed_dbl, &d, sizeof(double));
	dbl.sign = (!((parsed_dbl >> 63) & 1) * 2) - 1;
	while (--i > 0)
	{
		exp += ((parsed_dbl >> (63 - i) & 1)) * base;
		base *= 2;
	}
	if (exp == 2047)
		return (ft_inf_cases(dbl, parsed_dbl));
	exp -= 1023;
	dbl.decimal = ft_getdbl_fraction(parsed_dbl, exp);
	dbl = ft_getdbl_exponent(dbl, exp);
	return (dbl);
}
