/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 13:10:34 by jhache            #+#    #+#             */
/*   Updated: 2017/11/20 18:23:45 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	count;

	count = 0;
	if (!s)
		return (NULL);
	ptr = ft_strnew(len);
	if (ptr != NULL)
	{
		while (count < len)
		{
			ptr[count] = s[start + count];
			++count;
		}
		ptr[count] = '\0';
	}
	return (ptr);
}
