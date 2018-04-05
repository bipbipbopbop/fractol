/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:59:35 by jhache            #+#    #+#             */
/*   Updated: 2017/12/18 16:36:28 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(intmax_t n, int fd)
{
	uintmax_t		i;
	uintmax_t		result;

	i = 1;
	result = (uintmax_t)((n < 0) ? (n * -1) : n);
	if (n < 0)
		ft_putchar_fd('-', fd);
	while (result / i > 9)
		i *= 10;
	if (n == 0)
		ft_putchar_fd('0', fd);
	else
	{
		while (i != 0)
		{
			ft_putchar_fd((result / i) + 48, fd);
			result %= i;
			i /= 10;
		}
	}
}
