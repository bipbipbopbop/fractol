/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 13:22:49 by jhache            #+#    #+#             */
/*   Updated: 2017/11/10 18:01:32 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*result;
	size_t	lens1;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	len = lens1 + ft_strlen(s2);
	result = ft_strnew(len);
	if (result != NULL)
	{
		result = ft_strcpy(result, s1);
		ft_strcpy(result + lens1, s2);
	}
	return (result);
}
