/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 12:39:36 by jhache            #+#    #+#             */
/*   Updated: 2017/11/20 18:19:06 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ptr;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		++i;
	ptr = ft_strnew((size_t)i);
	if (ptr != NULL)
	{
		i = 0;
		while (s[i] != '\0')
		{
			ptr[i] = f(i, s[i]);
			++i;
		}
	}
	return (ptr);
}
