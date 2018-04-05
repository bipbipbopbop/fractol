/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 13:38:48 by jhache            #+#    #+#             */
/*   Updated: 2017/11/20 18:24:16 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespaces(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	size_t	len;
	char	*result;
	size_t	i;
	size_t	k;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s) - 1;
	while (is_whitespaces(s[i]))
		++i;
	while (is_whitespaces(s[len]) && s[i])
		--len;
	k = (len - i) + 1;
	result = ft_strsub(s, i, k);
	return (result);
}
