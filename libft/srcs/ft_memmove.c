/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 18:52:33 by jhache            #+#    #+#             */
/*   Updated: 2017/11/09 13:30:58 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;

	p_dst = (unsigned char *)dst;
	p_src = (unsigned char *)src;
	if (p_dst > p_src)
	{
		p_dst += len - 1;
		p_src += len - 1;
		while (len--)
			*p_dst-- = *p_src--;
	}
	else
		dst = ft_memcpy(dst, src, len);
	return (dst);
}
