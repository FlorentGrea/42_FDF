/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getdbl_fraction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:19:39 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 18:19:40 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>

char	*ft_binary_pow(char *tmp, int i)
{
	int	j;
	int	div;
	int	remnant;

	j = 0;
	remnant = 0;
	tmp[0] = '1';
	while (i > 0)
	{
		while (ft_isdigit(tmp[j]) || remnant != 0)
		{
			if (tmp[j])
				div = ((tmp[j] - '0') * 10) / 2;
			else
				div = 0;
			tmp[j] = ((div / 10) + remnant) + '0';
			remnant = div % 10;
			j++;
		}
		j = 0;
		i--;
	}
	return (tmp);
}

char	*ft_add_tmp(char *ret, char *tmp)
{
	int	i;
	int	add;
	int	remnant;

	i = ft_strlen(tmp);
	add = 0;
	remnant = 0;
	while (--i >= 0)
	{
		if (ret[i])
			add = ret[i] - '0';
		else
			add = 0;
		add += tmp[i] - '0' + remnant;
		ret[i] = add % 10 + '0';
		remnant = add / 10;
	}
	free(tmp);
	return (ret);
}

char	*ft_getdbl_fraction(unsigned long long parsed_dbl, int exp)
{
	char	*ret;
	char	*tmp;
	int		i;
	int		y;

	y = 1;
	ret = ft_calloc(2001, sizeof(char));
	if (!ret)
		return (ret);
	i = 11;
	ret[0] = (exp != -1023) + 48;
	while (++i < 64)
	{
		if ((parsed_dbl >> (63 - i) & 1))
		{
			tmp = (char *)ft_calloc(60, sizeof(char));
			if (!tmp)
				return (ret);
			tmp = ft_binary_pow(tmp, y);
			ret = ft_add_tmp(ret, tmp);
			tmp = NULL;
		}
		y++;
	}
	return (ret);
}
