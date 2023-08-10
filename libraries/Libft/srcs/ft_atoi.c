/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:30:49 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 17:31:23 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_atoi(const char *str)
{
	int	ret;
	int	neg;

	ret = 0;
	if (!str)
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		neg = -1;
	else
		neg = 1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
		ret = (ret * 10) + (*str++ - 48);
	return (ret * neg);
}
