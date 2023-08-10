/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getdbl_exponent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:19:34 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 18:19:35 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

t_dbl	ft_dbl_negexp(t_dbl data, int exp)
{
	int		add;
	int		div;
	char	*tmp;

	data.pow = 0;
	add = 0;
	while (exp++ < 0)
	{
		tmp = data.decimal;
		while (*tmp || add)
		{
			div = 0;
			if (*tmp)
				div = ((*tmp - 48) * 10) / 2;
			*tmp++ = ((div / 10) + add) + 48;
			add = div % 10;
		}
	}
	tmp = data.decimal;
	while (*tmp == '0')
		tmp++;
	data.pow = data.decimal - tmp;
	ft_memmove(data.decimal, tmp, ft_strlen(tmp));
	ft_bzero(data.decimal + ft_strlen(tmp), 2000 - ft_strlen(tmp));
	return (data);
}

void	ft_posexp_calc(t_dbl data, int exp)
{
	char	*tmp;
	int		add;
	int		save;

	while (exp--)
	{
		tmp = data.decimal + 2000;
		while (*--tmp || save == 38)
		{
			add = save == 38;
			save = 48;
			if (*tmp && *tmp > '4')
				save = 38;
			if (*tmp)
				*tmp = ((*tmp - 48) * 2) + save + add;
			else
				*tmp = 48 + add;
		}
	}
	tmp = NULL;
}

t_dbl	ft_dbl_posexp(t_dbl data, int exp)
{
	int		size;
	char	*tmp;

	data.pow = 0;
	size = ft_strlen(data.decimal);
	ft_memmove(data.decimal + 2000 - size, data.decimal, size);
	ft_bzero(data.decimal, size);
	ft_posexp_calc(data, exp);
	tmp = data.decimal;
	while (!*tmp)
		tmp++;
	data.pow = ft_strlen(tmp) - size;
	ft_memmove(data.decimal, tmp, ft_strlen(tmp));
	ft_bzero(data.decimal + ft_strlen(tmp), 2000 - ft_strlen(tmp));
	tmp = NULL;
	return (data);
}

t_dbl	ft_getdbl_exponent(t_dbl data, int exp)
{
	char	*tmp;

	tmp = data.decimal;
	while (*tmp == '0')
		tmp++;
	if (!*tmp)
		data.pow = 0;
	else if (exp < 0)
		return (ft_dbl_negexp(data, exp));
	else if (exp >= 0)
		return (ft_dbl_posexp(data, exp));
	tmp = NULL;
	return (data);
}
