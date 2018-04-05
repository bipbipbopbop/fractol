/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:56:09 by jhache            #+#    #+#             */
/*   Updated: 2017/12/15 14:11:35 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*charmod(const char *haystack, const char *needle)
{
	int		i;
	int		len;
	int		pos;

	i = 0;
	len = ft_strlen(needle);
	if (len == 0)
		return ((char *)haystack);
	while (haystack[i])
	{
		pos = 0;
		while (needle[pos])
		{
			if (needle[pos] == haystack[i])
				return ((char *)haystack + i);
			++pos;
		}
		++i;
	}
	return (NULL);
}

static char	*strmod(const char *haystack, const char *needle)
{
	int		i;
	int		len;
	int		pos;

	i = 0;
	len = ft_strlen(needle);
	if (len == 0)
		return ((char *)haystack);
	while (haystack[i])
	{
		pos = 0;
		while (needle[pos] == haystack[pos + i])
		{
			if (pos == (len - 1))
				return ((char *)haystack + i);
			++pos;
		}
		++i;
	}
	return (NULL);
}

char		*ft_strstr(const char *haystack, const char *needle, int flag)
{
	if (flag == STR)
		return (strmod(haystack, needle));
	if (flag == CHAR)
		return (charmod(haystack, needle));
	return (NULL);
}
