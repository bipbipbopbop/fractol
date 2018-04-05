/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversioncs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:07:49 by jhache            #+#    #+#             */
/*   Updated: 2018/01/08 14:47:20 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_convlc(wint_t c)
{
	char	*s;

	s = ft_strnew(4);
	if (c < 0b100000000)
		s[0] = c;
	else if (c < 0b100000000000)
	{
		s[1] = ((c & 0b00111111) | 0b10000000);
		s[0] = (((c >> 6) & 0b00011111) | 0b11000000);
	}
	else if (c < 0b10000000000000000)
	{
		s[2] = ((c & 0b00111111) | 0b10000000);
		s[1] = (((c >> 6) & 0b00111111) | 0b10000000);
		s[0] = (((c >> 12) & 0b00001111) | 0b11100000);
	}
	else if (c < 0b100010000000000000000)
	{
		s[3] = ((c & 0b00111111) | 0b10000000);
		s[2] = (((c >> 6) & 0b00111111) | 0b10000000);
		s[1] = (((c >> 12) & 0b00111111) | 0b10000000);
		s[0] = (((c >> 18) & 0b00000111) | 0b11110000);
	}
	return (s);
}

static char	*ft_convlccall(wint_t chr)
{
	char	*tmp;

	tmp = (((chr >= 0xD800 && chr <= 0xDFFF) || chr < 0
			|| chr > 1114111) ? NULL : ft_convlc(chr));
	if (tmp != NULL && MB_CUR_MAX < (int)ft_strlen(tmp))
		ft_strdel(&tmp);
	return (tmp);
}

char		*ft_convc(t_opt *opt, va_list ap)
{
	char	*result;
	int		chr;

	chr = va_arg(ap, int);
	if (ft_strequ(opt->len_modif, "l") == 0 && opt->conversion == 'c')
	{
		result = ft_strnew(1);
		result[0] = chr;
	}
	else
		result = ft_convlccall((wint_t)chr);
	if (result == NULL)
		ft_count_return(-1);
	return (result);
}

char		*ft_convls(t_opt *opt, va_list ap)
{
	char	*result;
	wchar_t	*uni_s;
	int		i;
	char	*tmp;

	i = -1;
	opt->precision = (opt->precision == UNDEFINED) ? INT_MAX : opt->precision;
	if ((uni_s = va_arg(ap, wchar_t *)) != NULL)
	{
		result = ft_strnew(0);
		while (uni_s[++i] && opt->precision > PREC_NULL)
		{
			tmp = ft_convlccall(uni_s[i]);
			if (tmp == NULL || (opt->precision -= ft_strlen(tmp)) >= 0)
				result = ft_strjoinfree(result, tmp, FIRST);
			ft_strdel(&tmp);
		}
	}
	else
		result = opt->precision >= PREC_NULL && opt->precision < 6
			? ft_strsub("(null)", 0, opt->precision) : ft_strdup("(null)");
	if (result == NULL)
		ft_count_return(-1);
	return (result);
}

char		*ft_convs(t_opt *opt, va_list ap)
{
	char	*result;
	char	*tmp;

	if (ft_strequ(opt->len_modif, "l") == 1)
		return (ft_convls(opt, ap));
	if ((result = ft_strdup(va_arg(ap, char *))) == NULL)
		result = ft_strdup("(null)");
	if (opt->precision != UNDEFINED && (int)ft_strlen(result) > opt->precision)
	{
		tmp = ft_strsub(result, 0, opt->precision);
		ft_strdel(&result);
		result = tmp;
	}
	return (result);
}
