/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:11:40 by jhache            #+#    #+#             */
/*   Updated: 2017/12/18 16:11:40 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*var_compute(unsigned long long *result, long long n, int *len)
{
	char	*str;

	*len = 1;
	*result = (unsigned long long)((n < 0) ? (n * -1) : n);
	if (n < 0)
		++(*len);
	while (n > 9 || n < -9)
	{
		++(*len);
		n /= 10;
	}
	str = ft_strnew(*len);
	return (str);
}

char			*ft_llitoa(long long n)
{
	unsigned long long	i;
	unsigned long long	result;
	int					len;
	char				*str;
	int					j;

	j = 0;
	i = 1;
	if ((str = var_compute(&result, n, &len)) == NULL)
		return (str);
	if (n < 0)
	{
		str[j++] = '-';
		--len;
	}
	while (--len > 0)
		i *= 10;
	while (i > 0)
	{
		str[j++] = (result / i) + 48;
		result %= i;
		i /= 10;
	}
	return (str);
}
