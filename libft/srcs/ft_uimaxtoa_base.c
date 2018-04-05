/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uimaxtoa_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 17:37:35 by jhache            #+#    #+#             */
/*   Updated: 2017/12/18 17:57:45 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*var_compute(uintmax_t n, int *len)
{
	char	*str;

	*len = 1;
	while (n > 9)
	{
		++(*len);
		n /= 10;
	}
	str = ft_strnew(*len);
	return (str);
}

char			*ft_uimaxtoa_base(uintmax_t n, char *base_from, char *base_to)
{
	uintmax_t	i;
	int			len;
	char		*str;
	int			j;

	j = 0;
	i = 1;
	if ((str = var_compute(n, &len)) == NULL)
		return (str);
	while (--len > 0)
		i *= 10;
	while (i > 0)
	{
		str[j++] = (n / i) + 48;
		n %= i;
		i /= 10;
	}
	return (ft_convert_base(str, base_from, base_to));
}
