/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round_dbl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:14:39 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 18:14:39 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

t_dbl	ft_new_decimal(t_dbl value, int size)
{
	free(value.decimal);
	value.decimal = NULL;
	if (size == 0)
		value.decimal = (char *)ft_calloc(2, sizeof(char));
	else if (!value.decimal)
		value.decimal = (char *)ft_calloc(size + 1, sizeof(char));
	if (!value.decimal)
		return (value);
	*(value.decimal) = '1';
	value.pow++;
	return (value);
}

int	ft_check_bankers(char *s)
{
	while (*++s)
		if (*s != '0' && *s)
			return (0);
	return (1);
}

void	ft_bankers_rounding(char *s, int i)
{
	s[i - 1] = s[i - 1] + 1;
	s[i] = '0';
}

t_dbl	ft_round_dbl(t_dbl value, int size)
{
	int	i;

	i = 0;
	if (value.decimal[size] == '5' && ft_check_bankers(value.decimal + size))
	{
		if (ft_strchr("13579", value.decimal[size - 1]))
			ft_bankers_rounding(value.decimal, size);
		return (value);
	}
	while (value.decimal[i] == '9' && i < size && value.decimal[i])
		i++;
	if (!value.decimal[i])
		return (value);
	if (i == size && value.decimal[i] > '4')
		return (ft_new_decimal(value, size));
	i = size;
	if (value.decimal[size] > '4')
	{
		while (value.decimal[--size] == '9' && size)
			value.decimal[size] = '0';
		value.decimal[size]++;
	}
	ft_memset(value.decimal + i, '0', ft_strlen(value.decimal + i));
	return (value);
}
