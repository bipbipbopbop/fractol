/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uimaxtoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 17:40:03 by jhache            #+#    #+#             */
/*   Updated: 2017/12/18 17:57:21 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*var_compute(uintmax_t n, size_t *len)
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

char			*ft_uimaxtoa(uintmax_t n)
{
	uintmax_t	i;
	size_t		len;
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
	return (str);
}
