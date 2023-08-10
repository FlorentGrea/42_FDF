/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:12:45 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 18:12:46 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

const char	*g_bases[] = {"0123456789", "01234567", "0123456789abcdef", \
	"0123456789ABCDEF", "0123456789abcdef"};

static int	ft_flag_h(t_printf d, t_flags flags, va_list ap)
{
	if (ft_search(d.s, "h") && *(ft_search(d.s, "h") - 1) == 'h')
		return (ft_format_hh_uint(d, flags, ap));
	else
		return (ft_format_h_uint(d, flags, ap));
}

static unsigned long long int	ft_get_ap_uint(va_list ap, const char *s)
{
	if (ft_search(s, "l") && *(ft_search(s, "l") - 1) == 'l')
		return (va_arg(ap, unsigned long long int));
	else if (ft_search(s, "l"))
		return ((unsigned long long int)va_arg(ap, unsigned long int));
	else if (ft_search(s, "h") && *(ft_search(s, "h") - 1) == 'h')
		return ((unsigned long long int)va_arg(ap, unsigned int));
	else if (ft_search(s, "h"))
		return ((unsigned long long int)va_arg(ap, unsigned int));
	else
		return ((unsigned long long int)va_arg(ap, unsigned int));
}

static int	ft_uint_size(unsigned long long int value, \
		const char *base, t_printf d, t_flags *flags)
{
	int	size;

	size = !(flags->prec == 0 && value == 0);
	if (*(d.s) != 'p' && ft_search(d.s, "#") && value != 0)
	{
		size += 2;
		flags->prec += 2;
	}
	if (flags->prec == 1 && value == 0)
		flags->prec = -1;
	while ((value / ft_strlen(base)) > 0 && size++)
		value /= ft_strlen(base);
	flags->prec -= size;
	flags->zero -= size;
	if (flags->prec > 0)
		size += flags->prec;
	else if (flags->prec < 0 && flags->zero > 0)
		size += flags->zero;
	return (((*(d.s) == 'p') * 2) + size);
}

static void	ft_putllu_fd(unsigned long long int nbr, const char *base, int fd)
{
	if (nbr > (ft_strlen(base) - 1))
		ft_putllu_fd(nbr / ft_strlen(base), base, fd);
	ft_putchar_fd(base[nbr % ft_strlen(base)], fd);
}

int	ft_format_uint(t_printf d, t_flags flags, va_list ap)
{
	const char				*base;
	int						size;
	unsigned long long int	v;

	if (ft_search(d.s, "h") && *d.s != 'p')
		return (ft_flag_h(d, flags, ap));
	base = g_bases[ft_strchr("uoxXp", *(d.s)) - "uoxXp"];
	if (*(d.s) == 'p')
		v = va_arg(ap, unsigned long long int);
	else
		v = ft_get_ap_uint(ap, d.s);
	size = ft_uint_size(v, base, d, &flags);
	if (flags.nbr > size)
		d.ret += ft_flag_number(flags, size);
	if (((ft_search(d.s, "#") && v != 0) || *(d.s) == 'p') && *(d.s) != 'u')
		ft_flag_hash(*(ft_strchr("uoxXp", *(d.s))));
	if (flags.zero > 0 && flags.min <= 0)
		ft_flag_zero(flags);
	if (flags.prec > 0)
		ft_flag_prec(flags);
	if (!(flags.prec == 0 && v == 0))
		ft_putllu_fd(v, base, 1);
	if (flags.min > size)
		d.ret += ft_flag_min(flags, size);
	return (d.ret + size);
}
