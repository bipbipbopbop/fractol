/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:14:30 by jhache            #+#    #+#             */
/*   Updated: 2018/03/28 13:07:22 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mouse_hook(int button, int x, int y, void *param)
{
	t_fractol	*frctl;

	frctl = (t_fractol *)param;
	return (0);
}

int		key_hook(int keycode, void *param)
{
	t_fractol	*frctl;

	frctl = (t_fractol *)param;
	if (keycode == 53)
	{
		ft_deallocate(frctl, frctl->ptr);
		exit(0);
	}
	else if (keycode == 15)
		ft_reset(frctl);
	else if (keycode == 69 || keycode == 78)
		ft_zoom(frctl, ((keycode == 69) ? 1 : -1));//MTN BINDER SUR LA MOLETTE, A SUPPRIMER
	else if (keycode == 35 || keycode == 46)
		ft_change_max_iter(frctl, ((keycode == 35) ? 1 : -1));
	else
		ft_printf("touche = %d\n", keycode);
	return (0);
}
