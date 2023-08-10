/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:07:25 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 18:09:12 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

const t_form_f	g_form_fct[] = {{'c', &ft_format_c}, {'s', &ft_format_s}, \
	{'p', &ft_format_uint}, {'d', &ft_format_int}, \
	{'i', &ft_format_int}, {'u', &ft_format_uint}, \
	{'o', &ft_format_uint}, {'x', &ft_format_uint}, \
	{'X', &ft_format_uint}, {'n', &ft_format_n}, \
	{'f', &ft_format_f}, {'g', &ft_format_g}, \
	{'e', &ft_format_e}, {'%', &ft_format_percent}};

static t_printf	ft_format_treatment(t_printf data, va_list ap)
{
	static char	*format_list = "cspdiuoxXnfge%";
	int			k;
	t_flags		flags;

	k = 0;
	flags = ft_flag_asterisk(data.s, ap);
	data.s++;
	while (*(data.s) && ft_strchr("-.*lh# +0123456789$", *(data.s)))
		data.s++;
	if (*(data.s) && ft_strchr(format_list, *(data.s)))
	{
		while (g_form_fct[k].format != *ft_strchr(format_list, *(data.s)))
			k++;
		data.ret = g_form_fct[k].fct(data, flags, ap);
		data.s++;
	}
	return (data);
}

int	ft_printf(const char *s, ...)
{
	t_printf	data;
	va_list		ap;

	data.s = s;
	data.ret = 0;
	va_start(ap, s);
	while (*(data.s))
	{
		if (ft_strchr(data.s, '%'))
		{
			write(1, data.s, ft_strchr(data.s, '%') - data.s);
			data.ret += ft_strchr(data.s, '%') - data.s;
			data.s = ft_strchr(data.s, '%');
			data = ft_format_treatment(data, ap);
		}
		else
		{
			ft_putstr_fd((char *)data.s, 1);
			data.ret += ft_strlen(data.s);
			data.s += ft_strlen(data.s);
		}
	}
	va_end(ap);
	return (data.ret);
}
