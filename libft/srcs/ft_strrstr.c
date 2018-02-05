/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 15:15:04 by jhache            #+#    #+#             */
/*   Updated: 2017/12/15 14:10:41 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*charmod(const char *haystack, const char *needle)
{
	int		i;
	int		len;
	int		pos;

	i = ft_strlen(haystack);
	len = ft_strlen(needle);
	while (haystack[i])
	{
		--i;
		pos = 0;
		while (needle[pos])
		{
			if (needle[pos] == haystack[i])
				return ((char *)haystack + i);
			++pos;
		}
	}
	return (NULL);
}

static char	*strmod(const char *haystack, const char *needle)
{
	int		i;
	int		len;
	int		pos;

	i = ft_strlen(haystack);
	len = ft_strlen(needle);
	while (i > 0)
	{
		--i;
		pos = 0;
		while (needle[pos] == haystack[pos + i])
		{
			if (pos == (len - 1))
				return ((char *)haystack + i);
			++pos;
		}
	}
	return (NULL);
}

char		*ft_strrstr(const char *haystack, const char *needle, int flag)
{
	if (haystack == NULL)
		return (NULL);
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	if (flag == STR)
		return (strmod(haystack, needle));
	if (flag == CHAR)
		return (charmod(haystack, needle));
	return (NULL);
}
