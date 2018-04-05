/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:29:45 by jhache            #+#    #+#             */
/*   Updated: 2018/01/10 14:47:50 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen(intmax_t n)
{
	size_t	i;

	i = 1;
	while (n > 9 || n < -9)
	{
		++i;
		n /= 10;
	}
	return (i);
}