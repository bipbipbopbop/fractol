/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:20:09 by jhache            #+#    #+#             */
/*   Updated: 2018/04/04 20:52:06 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	update_fract(t_fractol *frctl)
{
	size_t		work_size;

	work_size = X_SIZE * Y_SIZE;
	if (frctl->fract.name == julia)
	{
		frctl->status.cursor_pos_param[0] = frctl->status.x;
		frctl->status.cursor_pos_param[1] = frctl->status.y;
		ocl_julia(frctl, &work_size);
	}
	else if (frctl->fract.name == multibrot)
	{
		frctl->status.cursor_pos_param[0] =
			(int)frctl->status.x * 30 / X_SIZE;
		ocl_multibrot(frctl, &work_size);
	}
	mlx_clear_window(frctl->mlx->mlxptr, frctl->mlx->win);
	mlx_put_image_to_window(frctl->mlx->mlxptr, frctl->mlx->win,
			frctl->mlx->img->ptr, 0, 0);
}

int			ft_get_cursor_pos(int x, int y, void *param)
{
	t_fractol	*frctl;

	frctl = (t_fractol *)param;
	frctl->status.x = x;
	frctl->status.y = y;
	if (frctl->status.stop == 0
			&& (frctl->fract.name == julia || frctl->fract.name == multibrot))
		update_fract(frctl);
	return (0);
}

int			ft_mouse_event(int button, int x, int y, void *param)
{
	t_fractol	*frctl;

	frctl = (t_fractol *)param;
	frctl->status.x = x;
	frctl->status.y = y;
	if (button == SCROLLUP_KEY || button == SCROLLDOWN_KEY)
		ft_zoom(frctl, ((button == SCROLLUP_KEY) ? 1 : -1));
	return (0);
}
