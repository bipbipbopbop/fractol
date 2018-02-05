/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ullitoa_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 17:34:15 by jhache            #+#    #+#             */
/*   Updated: 2018/01/05 18:25:09 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*var_compute(unsigned long long n, int *len)
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

char		*ft_ullitoa_base(unsigned long long n,
							char *base_from, char *base_to)
{
	unsigned long long	i;
	int					len;
	char				*str;
	int					j;

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
