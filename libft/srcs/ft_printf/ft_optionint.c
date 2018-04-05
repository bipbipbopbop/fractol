/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_optionint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 18:28:14 by jhache            #+#    #+#             */
/*   Updated: 2018/01/08 13:40:16 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define PART1	1
#define PART2	2
#define PART3	3
#define NOGO	0

static char	*ft_attribute(t_opt *opt, char *s, int flag, int paddbool)
{
	char	*result;

	result = s;
	if (flag == PART1 && ft_strchr(opt->attribute, '+') != NULL
		&& ft_strchr("dDi", opt->conversion) != NULL && s[0] != '-')
		result = ft_strjoinfree("+", s, SECOND);
	if (flag == PART2 && ft_strchr(opt->attribute, '#') != NULL
		&& (ft_strstr(s, "123456789ABCDEFabcdef", CHAR) != NULL
			|| s[0] == 0))
	{
		if ((opt->conversion == 'o' || opt->conversion == 'O') && s[0] != '0')
			result = ft_strjoinfree("0", s, SECOND);
		else if (opt->conversion == 'X' && s[0] != 0)
			result = ft_strjoinfree("0X", s, SECOND);
		else if (opt->conversion == 'x' && s[0] != 0)
			result = ft_strjoinfree("0x", s, SECOND);
	}
	else if (flag == PART3 && paddbool == 1)
		s[0] = ' ';
	else if (flag == PART3 && paddbool == 0)
		result = ft_strjoinfree(" ", s, SECOND);
	return (result);
}

static char	*ft_precision(t_opt *opt, char *s)
{
	int		i;
	char	*result;
	char	*padding;

	i = opt->precision - ft_strlen(s);
	if (ft_strchr(s, '-') != NULL)
		++i;
	if (opt->precision == PREC_NULL && s[0] == '0')
		result = ft_strnew(0);
	else if (i > 0 && ft_strchr("dDioOuUxXb", opt->conversion) != NULL)
	{
		padding = ft_strnew(i);
		ft_memset(padding, '0', i);
		result = ft_strjoinfree(padding, s, FIRST);
	}
	else
		return (s);
	ft_strdel(&s);
	return (result);
}

static char	*ft_field_width(t_opt *opt, char *s, int slen)
{
	char	*padding;

	padding = ft_strnew(slen);
	if (ft_strchr(opt->attribute, '0') != NULL
		&& ft_strchr(opt->attribute, '-') == NULL
		&& (ft_strchr("dDioOuUxXb", opt->conversion) == NULL
		|| opt->precision == UNDEFINED))
		ft_memset(padding, '0', slen);
	else
		ft_memset(padding, ' ', slen);
	s = (ft_strchr(opt->attribute, '-') != NULL && opt->conversion != 'n') ?
		ft_strjoinfree(s, padding, BOTH) : ft_strjoinfree(padding, s, BOTH);
	return (s);
}

/*
** option : this function applies each specified options
** (precision, attribute, etc.) to the computed conversion string,
** with the attribute, precision and field_width functions.
** optionint is made for integer conversion.
*/

char		*ft_optionint(t_opt *opt, char *s)
{
	int		slen;

	if (s == NULL)
		return (NULL);
	s = ft_precision(opt, s);
	s = ft_attribute(opt, s, PART1, 0);
	if (ft_strchr(opt->attribute, '0') == NULL
		|| (ft_strchr(opt->attribute, '-') != NULL
			|| opt->precision != UNDEFINED))
		s = ft_attribute(opt, s, PART2, 0);
	else if (ft_strchr(opt->attribute, '#') != NULL && s[0] != '0')
		opt->field -= ((ft_strchr("oO", opt->conversion) != NULL) ? 1 : 2);
	slen = opt->field - ft_strlen(s);
	if (slen > 0)
		s = ft_field_width(opt, s, slen);
	if (ft_strchr(opt->attribute, '0') != NULL
		&& ft_strchr(opt->attribute, '-') == NULL
		&& opt->precision == UNDEFINED)
		s = ft_attribute(opt, s, PART2, 0);
	if (ft_strchr(opt->attribute, ' ') != NULL
		&& ft_strchr("dDi", opt->conversion) != NULL
		&& ft_strstr(s, "-+", CHAR) == NULL)
		s = ft_attribute(opt, s, PART3, ((slen > 0) ? 1 : NOGO));
	return (s);
}

/*
** replacesign : it's a tool function who place
** the '-' char at the right place in the string.
*/

char		*ft_replacesign(char *s, t_opt *opt)
{
	int		i;
	char	sign;
	char	*tmp;

	if (s != NULL && ft_strchr("dDi", opt->conversion) != NULL
		&& (tmp = ft_strstr(s, "-+", CHAR)) != NULL)
	{
		i = (int)(tmp - s);
		sign = *tmp;
		if (i == 0)
			return (s);
		else if (s[i - 1] == '0')
		{
			s[i] = '0';
			i = 0;
			while (s[i] != '0')
				++i;
			s[i] = sign;
		}
	}
	return (s);
}
