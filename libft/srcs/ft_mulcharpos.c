/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mulcharpos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 11:56:02 by jhache            #+#    #+#             */
/*   Updated: 2017/12/15 14:16:11 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** cette fonction, similaire a charpos, retourne l'index
** du char le plus proche dans le premier parametre
** correspondant a l'un des char de la chaine passer en second param.
** de meme que pour charpos, cette fonction assume que s[0] != c[ALL]
*/

#include "libft.h"

size_t	ft_mulcharpos(const char *s, const char *c)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (c[j])
		{
			if (s[i] == c[j])
				return (i);
			++j;
		}
		++i;
	}
	return (0);
}
