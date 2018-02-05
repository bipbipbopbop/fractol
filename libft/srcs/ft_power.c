/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:43:18 by jhache            #+#    #+#             */
/*   Updated: 2017/12/06 18:12:31 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_power(int nb, unsigned int power)
{
	long result;

	if (power == 0)
		return (1);
	result = nb;
	while (power > 1)
	{
		result *= nb;
		--power;
	}
	return (result);
}
