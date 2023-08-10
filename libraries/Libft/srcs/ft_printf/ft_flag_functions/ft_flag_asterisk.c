/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_asterisk.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:09:33 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 18:09:35 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

const char	*g_form = "cspdiuoxXnfge%";

static t_flags	ft_number(const char *s, va_list ap, t_flags flags)
{
	static char	*ignore = "# +";

	while (ft_strchr(ignore, *s))
		s++;
	if (*s == '*' || ft_strchr("1234567689", *s))
	{
		if (*s == '*')
			flags.nbr = va_arg(ap, int);
		else
			flags.nbr = ft_atoi(s);
	}
	if (flags.nbr < 0)
	{
		flags.min = flags.nbr;
		flags.nbr = 0;
	}
	return (flags);
}

static t_flags	ft_min(const char *s, va_list ap, t_flags flags)
{
	static char	*ignore = "# +0-";

	while (!ft_strchr(g_form, *s) && !ft_strchr("-.", *s))
		s++;
	if (*s++ == '-')
	{
		while (ft_strchr(ignore, *s))
			s++;
		if (*s == '*')
			flags.min = va_arg(ap, int);
		else
			flags.min = ft_atoi(s);
	}
	return (flags);
}

static t_flags	ft_prec(const char *s, va_list ap, t_flags flags)
{
	while (!ft_strchr(g_form, *s) && *s != '.')
		s++;
	if (*s++ == '.')
	{
		if (*s == '*')
			flags.prec = va_arg(ap, int);
		else
			flags.prec = ft_atoi(s);
	}
	if (flags.prec < 0)
		flags.prec = -1;
	return (flags);
}

static t_flags	ft_zero(const char *s, va_list ap, t_flags flags)
{
	static char	*forms = "0-.cspdiuoxXnfge%";
	static char	*ignore = "# +0";

	while (!ft_strchr(forms, *s))
		s++;
	if (*s++ == '0')
	{
		while (ft_strchr(ignore, *s))
			s++;
		if (*s == '*')
			flags.zero = va_arg(ap, int);
		else
			flags.zero = ft_atoi(s);
	}
	if (flags.zero < 0)
	{
		flags.min = flags.zero;
		flags.zero = 0;
	}
	return (flags);
}

t_flags	ft_flag_asterisk(const char *s, va_list ap)
{
	t_flags	flags;

	flags.nbr = 0;
	flags.min = 0;
	flags.prec = -1;
	flags.zero = 0;
	flags = ft_min(++s, ap, flags);
	if (flags.min == 0)
		flags = ft_number(s, ap, flags);
	if (flags.min == 0 && flags.nbr == 0)
		flags = ft_zero(s, ap, flags);
	flags = ft_prec(s, ap, flags);
	while (ft_strchr("0123456789 +-.#*", *s))
		s++;
	if (flags.prec > -1 && flags.zero > 0 && !ft_strchr("fge%", *s))
	{
		flags.nbr = flags.zero;
		flags.zero = 0;
	}
	flags.min *= (!(flags.min < 0) * 2) - 1;
	return (flags);
}
