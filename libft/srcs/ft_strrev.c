/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:13:46 by jhache            #+#    #+#             */
/*   Updated: 2017/12/14 15:37:12 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		end;
	char	tmp;
	int		i;

	i = 0;
	end = (ft_strlen(str) - 1);
	while (end > 0)
	{
		while (i < end)
		{
			tmp = str[i + 1];
			str[i + 1] = str[i];
			str[i] = tmp;
			++i;
		}
		--end;
		i = 0;
	}
	return (str);
}
