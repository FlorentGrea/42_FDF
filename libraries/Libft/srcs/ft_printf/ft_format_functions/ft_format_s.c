/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:12:35 by fgrea             #+#    #+#             */
/*   Updated: 2022/05/12 13:40:23 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

static void	ft_type_wchar(wchar_t data, int *ret)
{
	if (data <= 0x7f)
		ft_putchar_fd((data == 0) * '~' + (data != 0) * data, 1);
	else if (data <= 0x7FF)
	{
		ft_putchar_fd((((data & 0x07c0) >> 6) + 0xc0), 1);
		ft_putchar_fd(((data & 0x003F) + 0x80), 1);
		*ret += 1;
	}
	else if (data <= 0xFFFF)
	{
		ft_putchar_fd((((data & 0xF000) >> 12) + 0xE0), 1);
		ft_putchar_fd((((data & 0x0Fc0) >> 6) + 0x80), 1);
		ft_putchar_fd(((data & 0x003F) + 0x80), 1);
		*ret += 2;
	}
	else if (data <= 0x1FFFFF)
	{
		ft_putchar_fd((((data & 0x1c0000) >> 18) + 0xF0), 1);
		ft_putchar_fd((((data & 0x03F000) >> 12) + 0x80), 1);
		ft_putchar_fd((((data & 0x0Fc0) >> 6) + 0x80), 1);
		ft_putchar_fd(((data & 0x003F) + 0x80), 1);
		*ret += 3;
	}
}

static int	ft_str_size(wchar_t *data)
{
	int	i;

	i = 0;
	while (*data)
	{
		if (*data <= 0x7f || *data <= 0x7FF || *data <= 0xFFFF || \
				*data <= 0x1FFFFF)
			i++;
		data++;
	}
	return (i);
}

static int	ft_flags(t_printf *data, t_flags flags, int size)
{
	if ((flags.prec > 0 || (flags.prec == 0 && ft_search(data->s, "."))) && \
			(size > flags.prec))
		size = flags.prec;
	if (flags.nbr > size)
		data->ret += ft_flag_number(flags, size);
	return (size);
}

static int	ft_format_ls(t_printf data, t_flags flags, va_list ap)
{
	wchar_t	*str;
	int		size;
	int		i;

	i = 0;
	str = va_arg(ap, wchar_t *);
	if (!str)
		str = (wchar_t *)("(null)");
	if (flags.prec == 0)
		size = 0;
	else
		size = ft_str_size(str);
	size = ft_flags(&data, flags, size);
	if (flags.zero > (flags.prec > size ? flags.prec : size) && flags.min <= 0)
	{
		ft_flag_zero(flags);
		if (flags.zero - size > 0)
			data.ret += flags.zero - size;
	}
	while (i < size)
		ft_type_wchar(str[i++], &(data.ret));
	if (flags.min > size)
		data.ret += ft_flag_min(flags, size);
	return (data.ret + size);
}

int	ft_format_s(t_printf data, t_flags flags, va_list ap)
{
	char	*str;
	int		size;

	if (ft_search(data.s, "l"))
		return (ft_format_ls(data, flags, ap));
	str = va_arg(ap, char *);
	if (!str)
		str = "(null)";
	if (flags.prec == 0)
		size = 0;
	else
		size = ft_strlen(str);
	size = ft_flags(&data, flags, size);
	if (flags.zero > (flags.prec > size ? flags.prec : size) && flags.min <= 0)
	{
		flags.zero -= size;
		ft_flag_zero(flags);
		if (flags.zero > 0)
			data.ret += flags.zero;
	}
	write(1, str, size);
	if (flags.min > size)
		data.ret += ft_flag_min(flags, size);
	return (data.ret + size);
}
