/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charpos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:52:09 by jhache            #+#    #+#             */
/*   Updated: 2017/12/04 17:14:11 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** cette fonction assume que s[0] != c
*/

#include "libft.h"

size_t	ft_charpos(char const *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		++i;
	}
	return (0);
}
