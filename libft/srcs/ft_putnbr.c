/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:13:00 by jhache            #+#    #+#             */
/*   Updated: 2017/12/18 16:20:57 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(intmax_t n)
{
	uintmax_t	i;
	uintmax_t	result;

	i = 1;
	result = (uintmax_t)((n < 0) ? (n * -1) : n);
	if (n < 0)
		ft_putchar('-');
	while (result / i > 9)
		i *= 10;
	if (n == 0)
		ft_putchar('0');
	else
	{
		while (i != 0)
		{
			ft_putchar((result / i) + 48);
			result %= i;
			i /= 10;
		}
	}
}
