/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:14:30 by jhache            #+#    #+#             */
/*   Updated: 2018/04/02 17:14:07 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		key_hook(int keycode, void *param)
{
	t_fractol	*frctl;

	frctl = (t_fractol *)param;
	if (keycode == 53)
	{
		ft_deallocate(frctl, frctl->ptr);
		exit(0);
	}
	else if (keycode >= 18 && keycode <= 21)
		ft_change_color_type(frctl, keycode);
	else if (keycode == 15)
		ft_reset(frctl);
	else if (keycode == 69 || keycode == 78)
		ft_change_max_iter(frctl, ((keycode == 69) ? 1 : -1));
	else if (keycode == 34 || keycode == 31)
		ft_zoom(frctl, ((keycode == 34) ? 1 : -1));
	else if (keycode >= 123 && keycode <= 126)
		ft_move(frctl, keycode);
	else if (keycode == 1)
		frctl->status.stop = ((frctl->status.stop == 1) ? 0 : 1);
	return (0);
}
