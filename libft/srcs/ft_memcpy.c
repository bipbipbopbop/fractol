/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 18:39:19 by jhache            #+#    #+#             */
/*   Updated: 2017/11/20 18:04:16 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*t;

	t = (unsigned char *)dst;
	p = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		t[i] = p[i];
		++i;
	}
	return (dst);
}
