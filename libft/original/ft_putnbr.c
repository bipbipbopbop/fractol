/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:13:00 by jhache            #+#    #+#             */
/*   Updated: 2017/11/13 12:47:57 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int				i;
	unsigned int	result;

	i = 1;
	if (n < 0)
	{
		result = (unsigned int)(n * -1);
		ft_putchar('-');
	}
	else
		result = (unsigned int)n;
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
