/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 18:39:50 by jhache            #+#    #+#             */
/*   Updated: 2018/03/27 18:42:31 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_center_on_cursor(t_fractol *frctl, int where)
{
	int		x;
	int		y;
	float	speed;
	float	tmpx;
	float	tmpy;

	speed = ((where == 1) ? 0.25 : 0.1667);
	x = frctl->status.x;
	y = frctl->status.y;
	tmpx = X_SCALING(frctl->fract.x2, frctl->fract.x1);
	tmpy = Y_SCALING(frctl->fract.y2, frctl->fract.y1);
	if (where == 1)
	{
		frctl->fract.x1 += ((x - X_SIZE / 2) / tmpx) * speed;
		frctl->fract.x2 += ((x - X_SIZE / 2) / tmpx) * speed;
		frctl->fract.y1 += ((y - Y_SIZE / 2) / tmpy) * speed;
		frctl->fract.y2 += ((y - Y_SIZE / 2) / tmpy) * speed;
	}
	else
	{
		frctl->fract.x1 -= ((x - X_SIZE / 2) / tmpx) * speed;
		frctl->fract.x2 -= ((x - X_SIZE / 2) / tmpx) * speed;
		frctl->fract.y1 -= ((y - Y_SIZE / 2) / tmpy) * speed;
		frctl->fract.y2 -= ((y - Y_SIZE / 2) / tmpy) * speed;
	}
}

void	ft_zoom(t_fractol *frctl, int where)
{
	t_mlx	*mlx;
	float	zoomx;
	float	zoomy;
	size_t	work_size;

	work_size = X_SIZE * Y_SIZE;
	mlx = frctl->mlx;
	zoomx = (frctl->fract.x2 - frctl->fract.x1) * 0.1;
	zoomy = (frctl->fract.y2 - frctl->fract.y1) * 0.1;
	frctl->fract.x1 += ((where == 1) ? zoomx : (zoomx * -1));
	frctl->fract.x2 -= ((where == 1) ? zoomx : (zoomx * -1));
	frctl->fract.y1 += ((where == 1) ? zoomy : (zoomy * -1));
	frctl->fract.y2 -= ((where == 1) ? zoomy : (zoomy * -1));
	ft_center_on_cursor(frctl, where);
	mlx_destroy_image(mlx->mlxptr, mlx->img->ptr);
	mlx->img->ptr = mlx_new_image(mlx->mlxptr, X_SIZE, Y_SIZE);
	mlx->img->data = (int *)mlx_get_data_addr(mlx->img->ptr,
			&(mlx->img->bpp), &(mlx->img->linesize), &(mlx->img->endian));
	ocl_mandelbrot(frctl, &work_size);
	mlx_clear_window(mlx->mlxptr, mlx->win);
	mlx_put_image_to_window(mlx->mlxptr, mlx->win,
			frctl->mlx->img->ptr, 0, 0);
}
