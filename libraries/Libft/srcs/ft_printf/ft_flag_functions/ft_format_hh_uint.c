/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_hh_uint.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:11:31 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 18:11:31 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

const char	*g_hh_bases[] = {"0123456789", "01234567", "0123456789abcdef", \
	"0123456789ABCDEF", "0123456789abcdef"};

static int	ft_uint_size(unsigned char value, \
		const char *base, t_printf data, t_flags *flags)
{
	int	size;

	size = !(flags->prec == 0 && value == 0);
	if (*(data.s) != 'p' && ft_search(data.s, "#") && value != 0)
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
	return (((*(data.s) == 'p') * 2) + size);
}

static void	ft_putllu_fd(unsigned char nbr, const char *base, int fd)
{
	if (nbr > (ft_strlen(base) - 1))
		ft_putllu_fd(nbr / ft_strlen(base), base, fd);
	ft_putchar_fd(base[nbr % ft_strlen(base)], fd);
}

int	ft_format_hh_uint(t_printf data, t_flags flags, va_list ap)
{
	static char			*form = "uoxXp";
	const char			*base;
	int					size;
	unsigned char		v;

	base = g_hh_bases[ft_strchr(form, *(data.s)) - form];
	v = (unsigned char)va_arg(ap, unsigned int);
	size = ft_uint_size(v, base, data, &flags);
	if (flags.nbr > size)
		data.ret += ft_flag_number(flags, size);
	if (((ft_search(data.s, "#") && v != 0) || *(data.s) == 'p') && \
			*(data.s) != 'u')
		ft_flag_hash(*(ft_strchr(form, *(data.s))));
	if (flags.zero > 0 && flags.min <= 0)
		ft_flag_zero(flags);
	if (flags.prec > 0)
		ft_flag_prec(flags);
	if (!(flags.prec == 0 && v == 0))
		ft_putllu_fd(v, base, 1);
	if (flags.min > size)
		data.ret += ft_flag_min(flags, size);
	return (data.ret + size);
}
