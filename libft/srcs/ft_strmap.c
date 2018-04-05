/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 12:29:00 by jhache            #+#    #+#             */
/*   Updated: 2017/11/20 18:18:35 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*ptr;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = ft_strlen(s);
	ptr = ft_strnew(i);
	if (ptr != NULL)
	{
		i = 0;
		while (s[i])
		{
			ptr[i] = f(s[i]);
			++i;
		}
	}
	return (ptr);
}
