/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 18:46:48 by jhache            #+#    #+#             */
/*   Updated: 2017/11/20 18:04:05 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*t;

	p = (unsigned char *)dst;
	t = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		p[i] = t[i];
		if (p[i] == (unsigned char)c)
			return (&dst[i + 1]);
		++i;
	}
	return (NULL);
}
