/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversionmis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 18:32:57 by jhache            #+#    #+#             */
/*   Updated: 2018/01/10 16:44:16 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_convp(t_opt *opt, va_list ap)
{
	char		*result;
	void		*arg;
	static char	b10[] = "0123456789";
	static char	b16[] = "0123456789abcdef";

	if (opt->conversion != 'p')
		return (NULL);
	arg = va_arg(ap, void *);
	result = ft_ullitoa_base((uintptr_t)arg, b10, b16);
	result = ft_strjoinfree("0x", result, SECOND);
	return (result);
}

char	*ft_convpercent(t_opt *opt, va_list ap)
{
	char	*result;

	if (opt == NULL || ap == NULL)
		return (NULL);
	result = ft_strdup("%\0");
	return (result);
}

char	*ft_convb(t_opt *opt, va_list ap)
{
	char		*result;
	static char	b10[] = "0123456789";
	static char	b2[] = "01";

	if (ft_strequ(opt->len_modif, "l") == 1)
		result = ft_ullitoa_base(va_arg(ap, unsigned long), b10, b2);
	else if (ft_strequ(opt->len_modif, "ll") == 1)
		result = ft_ullitoa_base(va_arg(ap, unsigned long long), b10, b2);
	else if (ft_strequ(opt->len_modif, "j") == 1)
		result = ft_uimaxtoa_base(va_arg(ap, uintmax_t), b10, b2);
	else if (ft_strequ(opt->len_modif, "z") == 1)
		result = ft_uimaxtoa_base(va_arg(ap, size_t), b10, b2);
	else if (ft_strequ(opt->len_modif, "h") == 1)
		result = ft_ullitoa_base(
			(unsigned short int)va_arg(ap, unsigned int), b10, b2);
	else if (ft_strequ(opt->len_modif, "hh") == 1)
		result = ft_ullitoa_base(
			(unsigned char)va_arg(ap, unsigned int), b10, b2);
	else
		result = ft_ullitoa_base(va_arg(ap, unsigned int), b10, b2);
	return (result);
}
