/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 14:23:03 by jhache            #+#    #+#             */
/*   Updated: 2018/01/11 12:33:02 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int			check_base(char *base)
{
	int i;
	int j;

	i = 0;
	j = 1;
	if (ft_strlen(base) < 2 || *base == '-' || *base == '+' || *base < 33)
		return (0);
	while (base[j])
	{
		if (base[j] == '-' || base[j] == '+' || base[j] < 33)
			return (0);
		if (ft_strchr(base + j, base[i]) != NULL)
			return (0);
		++i;
		j = i + 1;
	}
	return (1);
}

static int			check_number(char *nbr, char *base_from, char *base_to)
{
	int i;
	int j;

	j = (nbr[0] == '-' || nbr[0] == '+') ? 1 : 0;
	while (nbr[j])
	{
		i = 0;
		while (nbr[j] != base_from[i] && base_from[i])
			++i;
		if (base_from[i] == '\0')
			return (0);
		++j;
	}
	if (check_base(base_from) == 0 || check_base(base_to) == 0)
		return (0);
	return (1);
}

static uintmax_t	base_to_decimal(char *nbr, char *base)
{
	int					i;
	int					j;
	int					k;
	uintmax_t			decimal;

	decimal = 0;
	j = (nbr[0] == '-' || nbr[0] == '+') ? 1 : 0;
	k = ft_strlen(base);
	while (nbr[j])
	{
		i = 0;
		while (nbr[j] != base[i])
			++i;
		decimal *= k;
		decimal += i;
		++j;
	}
	return (decimal);
}

/*
** for binary conversion, this function can't handle
** numbers that are bigger than INT_MAX.
** to correct this, change the strnew(64) line.
*/

char				*ft_convert_base(char *nb, char *base_from, char *base_to)
{
	uintmax_t			number;
	int					i;
	char				*result;
	int					k;

	i = 0;
	k = ft_strlen(base_to);
	if (check_number(nb, base_from, base_to) == 0)
		return (NULL);
	number = base_to_decimal(nb, base_from);
	if (k == 10)
		return (*nb != '-' ? ft_uimaxtoa(number) : ft_imaxtoa(number * -1));
	if ((result = ft_strnew(64)) == NULL)
		return (NULL);
	if (number == 0)
		result[0] = base_to[0];
	while (number != 0)
	{
		result[i++] = base_to[number % k];
		number /= k;
	}
	if (nb[0] == '-')
		result[i] = '-';
	return (ft_strrev(result));
}
