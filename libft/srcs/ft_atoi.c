/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:20:52 by jhache            #+#    #+#             */
/*   Updated: 2018/02/21 17:51:14 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' ||
			c == '\r' || c == ' ')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int		result;
	int		i;
	int		isneg;

	isneg = 1;
	i = 0;
	result = 0;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '-' && ft_isdigit(str[i + 1]))
	{
		isneg = -1;
		++i;
	}
	if (str[i] == '+')
		++i;
	while (ft_isdigit((int)str[i]))
	{
		result *= 10;
		result += (int)str[i] - 48;
		++i;
	}
	result *= isneg;
	return (result);
}
