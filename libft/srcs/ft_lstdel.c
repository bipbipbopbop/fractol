/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:27:57 by jhache            #+#    #+#             */
/*   Updated: 2017/11/13 17:33:54 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	**p;

	p = alst;
	if (alst == NULL)
		return ;
	while ((*p)->next != NULL)
	{
		del((*p)->content, (*p)->content_size);
		*p = (*p)->next;
	}
	del((*p)->content, (*p)->content_size);
	free(*alst);
	*alst = NULL;
}
