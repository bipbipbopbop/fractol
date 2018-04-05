/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 14:59:09 by jhache            #+#    #+#             */
/*   Updated: 2017/12/19 17:09:02 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoinfree(char *s1, char *s2, int flag)
{
	size_t	len;
	char	*result;
	size_t	lens1;

	result = NULL;
	if (s1 != NULL && s2 != NULL)
	{
		lens1 = ft_strlen(s1);
		len = lens1 + ft_strlen(s2);
		result = ft_strnew(len);
	}
	if (result != NULL)
	{
		result = ft_strcpy(result, s1);
		ft_strcpy(result + lens1, s2);
	}
	if ((flag == FIRST || flag == BOTH) && s1 != NULL)
		ft_strdel(&s1);
	if ((flag == SECOND || flag == BOTH) && s2 != NULL)
		ft_strdel(&s2);
	return (result);
}
