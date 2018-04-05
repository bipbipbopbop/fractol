/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:46:13 by jhache            #+#    #+#             */
/*   Updated: 2017/11/20 18:21:42 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && needle[j] != '\0' && i < len)
	{
		if (needle[j] == haystack[i])
			++j;
		else
		{
			i = i - j;
			j = 0;
		}
		++i;
	}
	if (j < ft_strlen(needle))
		return (NULL);
	return ((char *)&haystack[i - ft_strlen(needle)]);
}
