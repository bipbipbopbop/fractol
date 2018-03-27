/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:20:09 by jhache            #+#    #+#             */
/*   Updated: 2018/03/26 17:43:36 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_get_cursor_pos(int x, int y, void *param)
{
	t_fractol	*frctl;

	frctl = (t_fractol *)param;
	frctl->status.x = x;
	frctl->status.y = y;
	return (0);
}

int		ft_mouse_event(int button, int x, int y, void *param)
{
	t_fractol	*frctl;

	frctl = (t_fractol *)param;
	frctl->status.x = x;
	frctl->status.y = y;
	if (button == SCROLLUP_KEY || button == SCROLLDOWN_KEY)
		ft_zoom(frctl, ((button == SCROLLUP_KEY) ? 1 : -1));
	return (0);
}
