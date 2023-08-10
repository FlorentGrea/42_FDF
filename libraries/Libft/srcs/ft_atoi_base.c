/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:32:48 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 17:32:50 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_check(char *str)
{
	int	i;

	while (*str)
	{
		i = 1;
		if (*str == '-' || *str == '+')
			return (1);
		if ((*str >= 9 && *str <= 13) || *str == 32)
			return (1);
		while (str[i])
			if (*str == str[i++])
				return (1);
		str++;
	}
	return (0);
}

unsigned int	is_base(int s, char c, char *base)
{
	unsigned int	i;

	i = 0;
	while (base[i])
		if (base[i++] == c)
			return (i - 1);
	return (s + 1);
}

int	ft_atoi_base(char *str, char *base)
{
	unsigned int	s;
	int				ret;
	int				i;

	ret = 0;
	i = 1;
	s = ft_strlen(base);
	if (s < 2 || ft_check(base))
		return (ret);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str == '-' || *str == '+')
		if (*str++ == '-')
			i = i * -1;
	while (is_base(s, *str, base) != (s + 1) && *str)
		ret = ret * s + is_base(s, *str++, base);
	return (ret * i);
}
