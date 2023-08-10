/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrea <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:29:15 by fgrea             #+#    #+#             */
/*   Updated: 2021/11/09 17:29:18 by fgrea            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <wchar.h>

typedef struct s_dbl
{
	int				sign;
	char			*decimal;
	int				pow;
}					t_dbl;

typedef struct s_flags
{
	int				nbr;
	int				min;
	int				prec;
	int				zero;
}					t_flags;

typedef struct s_printf
{
	const char		*s;
	int				ret;
}					t_printf;

typedef struct s_form_f
{
	char			format;
	int				(*fct)(t_printf, t_flags, va_list);
}					t_form_f;

int					ft_printf(const char *s, ...);

char				*ft_search(const char *s, char *pos);

t_dbl				ft_getdbl(double d);
t_dbl				ft_getdbl_exponent(t_dbl data, int exp);
char				*ft_getdbl_fraction(unsigned long long parsed_dbl, int exp);
int					ft_dbl_case_e(t_printf data, t_flags flags, t_dbl v);
int					ft_dbl_case_f(t_printf data, t_flags flags, t_dbl v);

t_dbl				ft_round_dbl(t_dbl value, int size);

int					ft_format_c(t_printf data, t_flags flags, va_list ap);
int					ft_format_s(t_printf data, t_flags flags, va_list ap);
int					ft_format_int(t_printf data, t_flags flags, va_list ap);
int					ft_format_uint(t_printf data, t_flags flags, va_list ap);
int					ft_format_percent(t_printf data, t_flags flags, va_list ap);
int					ft_format_n(t_printf data, t_flags flags, va_list ap);
int					ft_format_f(t_printf data, t_flags flags, va_list ap);
int					ft_format_e(t_printf data, t_flags flags, va_list ap);
int					ft_format_g(t_printf data, t_flags flags, va_list ap);

t_flags				ft_flag_asterisk(const char *s, va_list ap);
int					ft_flag_number(t_flags flags, int size);
int					ft_flag_min(t_flags flags, int size);
void				ft_flag_zero(t_flags flags);
void				ft_flag_prec(t_flags flags);
void				ft_flag_plus(void);
void				ft_flag_spc(void);
void				ft_flag_hash(char format);

int					ft_format_h_int(t_printf data, t_flags flags, va_list ap);
int					ft_format_h_uint(t_printf data, t_flags flags, va_list ap);
int					ft_format_hh_int(t_printf data, t_flags flags, va_list ap);
int					ft_format_hh_uint(t_printf data, t_flags flags, va_list ap);

#endif
