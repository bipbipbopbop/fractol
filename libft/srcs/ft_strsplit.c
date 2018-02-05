/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:08:53 by jhache            #+#    #+#             */
/*   Updated: 2017/11/20 18:23:10 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		word_count(char const *s, char c)
{
	unsigned int	i;
	unsigned int	wrdnbr;
	unsigned int	is_wrd;

	is_wrd = 1;
	i = 0;
	wrdnbr = 0;
	while (s[i])
	{
		if (s[i] == c)
			is_wrd = 1;
		else if (is_wrd == 1)
		{
			is_wrd = 0;
			++wrdnbr;
		}
		++i;
	}
	return (wrdnbr);
}

static char		**f(char const *s, char c, char **result)
{
	unsigned int	start;
	unsigned int	a;
	int				i;

	i = 0;
	a = 0;
	while (s[a])
	{
		if (s[a] != c)
		{
			start = a;
			while (s[a] != c && s[a])
				++a;
			result[i] = ft_strsub(s, start, (size_t)(a - start));
			if (result[i++] == NULL)
				return (NULL);
		}
		else
			++a;
	}
	result[i] = 0;
	return (result);
}

char			**ft_strsplit(char const *s, char c)
{
	char			**result;

	if (!s)
		return (NULL);
	if (!(result = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1))))
		return (NULL);
	return (f(s, c, result));
}
