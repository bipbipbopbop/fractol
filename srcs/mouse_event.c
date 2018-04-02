/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:20:09 by jhache            #+#    #+#             */
/*   Updated: 2018/04/02 16:05:48 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_get_cursor_pos(int x, int y, void *param)
{
	t_fractol	*frctl;
	size_t		work_size;

	frctl = (t_fractol *)param;
	frctl->status.x = x;
	frctl->status.y = y;
	if (frctl->status.stop == 0 && frctl->fract.name == julia)
	{
		work_size = X_SIZE * Y_SIZE;
		frctl->status.cursor_pos_param[0] = x;
		frctl->status.cursor_pos_param[1] = y;
		ocl_julia(frctl, &work_size);
		mlx_clear_window(frctl->mlx->mlxptr, frctl->mlx->win);
		mlx_put_image_to_window(frctl->mlx->mlxptr, frctl->mlx->win,
				frctl->mlx->img->ptr, 0, 0);
	}
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
