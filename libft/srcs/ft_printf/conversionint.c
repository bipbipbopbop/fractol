/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversionint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:08:22 by jhache            #+#    #+#             */
/*   Updated: 2018/01/05 18:22:09 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_convd(t_opt *opt, va_list ap)
{
	char	*result;

	if (ft_strequ(opt->len_modif, "l") == 1 || opt->conversion == 'D')
		result = ft_llitoa(va_arg(ap, long));
	else if (ft_strequ(opt->len_modif, "ll") == 1)
		result = ft_llitoa(va_arg(ap, long long));
	else if (ft_strequ(opt->len_modif, "j") == 1)
		result = ft_imaxtoa(va_arg(ap, intmax_t));
	else if (ft_strequ(opt->len_modif, "z") == 1)
		result = ft_imaxtoa(va_arg(ap, ssize_t));
	else if (ft_strequ(opt->len_modif, "h") == 1)
		result = ft_itoa((short int)va_arg(ap, int));
	else if (ft_strequ(opt->len_modif, "hh") == 1)
		result = ft_itoa((char)va_arg(ap, int));
	else
		result = ft_itoa(va_arg(ap, int));
	return (result);
}

char		*ft_convu(t_opt *opt, va_list ap)
{
	char	*result;

	if (ft_strequ(opt->len_modif, "l") == 1 || opt->conversion == 'U')
		result = ft_ullitoa(va_arg(ap, unsigned long));
	else if (ft_strequ(opt->len_modif, "ll") == 1)
		result = ft_ullitoa(va_arg(ap, unsigned long long));
	else if (ft_strequ(opt->len_modif, "j") == 1)
		result = ft_uimaxtoa(va_arg(ap, uintmax_t));
	else if (ft_strequ(opt->len_modif, "z") == 1)
		result = ft_uimaxtoa(va_arg(ap, size_t));
	else if (ft_strequ(opt->len_modif, "h") == 1)
		result = ft_ullitoa((unsigned short int)va_arg(ap, unsigned int));
	else if (ft_strequ(opt->len_modif, "hh") == 1)
		result = ft_ullitoa((unsigned char)va_arg(ap, unsigned int));
	else
		result = ft_ullitoa(va_arg(ap, unsigned int));
	return (result);
}

char		*ft_convo(t_opt *opt, va_list ap)
{
	char		*result;
	static char	b10[] = "0123456789";
	static char	b8[] = "01234567";

	if (ft_strequ(opt->len_modif, "l") == 1 || opt->conversion == 'O')
		result = ft_ullitoa_base(va_arg(ap, unsigned long), b10, b8);
	else if (ft_strequ(opt->len_modif, "ll") == 1)
		result = ft_ullitoa_base(va_arg(ap, unsigned long long), b10, b8);
	else if (ft_strequ(opt->len_modif, "j") == 1)
		result = ft_uimaxtoa_base(va_arg(ap, uintmax_t), b10, b8);
	else if (ft_strequ(opt->len_modif, "z") == 1)
		result = ft_uimaxtoa_base(va_arg(ap, size_t), b10, b8);
	else if (ft_strequ(opt->len_modif, "h") == 1)
		result = ft_ullitoa_base(
			(unsigned short int)va_arg(ap, unsigned int), b10, b8);
	else if (ft_strequ(opt->len_modif, "hh") == 1)
		result = ft_ullitoa_base(
			(unsigned char)va_arg(ap, unsigned int), b10, b8);
	else
		result = ft_ullitoa_base(va_arg(ap, unsigned int), b10, b8);
	return (result);
}

char		*ft_convx(t_opt *opt, va_list ap)
{
	char		*result;
	static char	b10[] = "0123456789";
	static char	b16[] = "0123456789abcdef";

	if (ft_strequ(opt->len_modif, "l") == 1)
		result = ft_ullitoa_base(va_arg(ap, unsigned long), b10, b16);
	else if (ft_strequ(opt->len_modif, "ll") == 1)
		result = ft_ullitoa_base(va_arg(ap, unsigned long long), b10, b16);
	else if (ft_strequ(opt->len_modif, "j") == 1)
		result = ft_uimaxtoa_base(va_arg(ap, uintmax_t), b10, b16);
	else if (ft_strequ(opt->len_modif, "z") == 1)
		result = ft_uimaxtoa_base(va_arg(ap, size_t), b10, b16);
	else if (ft_strequ(opt->len_modif, "h") == 1)
		result = ft_ullitoa_base(
			(unsigned short int)va_arg(ap, unsigned int), b10, b16);
	else if (ft_strequ(opt->len_modif, "hh") == 1)
		result = ft_ullitoa_base(
			(unsigned char)va_arg(ap, unsigned int), b10, b16);
	else
		result = ft_ullitoa_base(va_arg(ap, unsigned int), b10, b16);
	if (opt->conversion == 'X')
		ft_striter(result, &ft_toupper);
	return (result);
}
