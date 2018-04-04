/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 18:39:50 by jhache            #+#    #+#             */
/*   Updated: 2018/04/04 21:24:59 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_center_on_cursor(t_fractol *frctl, int where)
{
	int		x;
	int		y;
	t_real	speed;
	t_real	tmpx;
	t_real	tmpy;

	speed = ((where == 1) ? 0.06333 : 0.05667);
	x = frctl->status.x;
	y = frctl->status.y;
	tmpx = X_SCALING(frctl->fract.x2, frctl->fract.x1);
	tmpy = Y_SCALING(frctl->fract.y2, frctl->fract.y1);
	frctl->fract.x1 += ((x - X_SIZE / 2) / tmpx) * speed * where;
	frctl->fract.x2 += ((x - X_SIZE / 2) / tmpx) * speed * where;
	frctl->fract.y1 += ((y - Y_SIZE / 2) / tmpy) * speed * where;
	frctl->fract.y2 += ((y - Y_SIZE / 2) / tmpy) * speed * where;
}

void		ft_zoom(t_fractol *frctl, int where)
{
	t_mlx	*mlx;
	t_real	zoomx;
	t_real	zoomy;
	size_t	work_size;
	int		i;

	work_size = X_SIZE * Y_SIZE;
	mlx = frctl->mlx;
	zoomx = (frctl->fract.x2 - frctl->fract.x1) * 0.03;
	zoomy = (frctl->fract.y2 - frctl->fract.y1) * 0.03;
	if (where == 1 && (zoomx < 0.0000001 || zoomy < 0.0000001))
		return ;
	frctl->fract.x1 += zoomx * where;
	frctl->fract.x2 -= zoomx * where;
	frctl->fract.y1 += zoomy * where;
	frctl->fract.y2 -= zoomy * where;
	ft_center_on_cursor(frctl, where);
	i = 0;
	while (g_fract[i].name != frctl->fract.name)
		++i;
	g_fract[i].fun_ptr(frctl, &work_size);
	mlx_clear_window(mlx->mlxptr, mlx->win);
	mlx_put_image_to_window(mlx->mlxptr, mlx->win,
			frctl->mlx->img->ptr, 0, 0);
}
