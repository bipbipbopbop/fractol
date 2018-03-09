/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:14:30 by jhache            #+#    #+#             */
/*   Updated: 2018/03/09 17:31:47 by jhache           ###   ########.fr       */
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
	else if (keycode == 69 || keycode == 78)
		ft_zoom(frctl, ((keycode == 69) ? 1 : -1));
	return (0);
}

void	ft_zoom(t_fractol *frctl, int where)
{
	t_mlx	*mlx;
	float	tmpx;
	float	tmpy;
	float	speed;

	mlx = frctl->mlx;
	tmpx = X_SCALING(frctl->fract.x2, frctl->fract.x1);
	tmpy = Y_SCALING(frctl->fract.y2, frctl->fract.y1);
/*	speed = 0.03;
	if (where == 1 && (frctl->fract.x1 + (speed * 2) > frctl->fract.x2
				|| frctl->fract.y1 + (speed * 2) > frctl->fract.y2))
				return ;*/
	frctl->fract.x1 += (((where == 1) ? 0.1 : -0.1) * (tmpx / tmpy));
	frctl->fract.x2 -= (((where == 1) ? 0.1 : -0.1) * (tmpx / tmpy));
	frctl->fract.y1 += (((where == 1) ? 0.1 : -0.1) * (tmpy / tmpx));
	frctl->fract.y2 -= (((where == 1) ? 0.1 : -0.1) * (tmpy / tmpx));
/*	frctl->fract.x1 += (((where == 1) ? speed : (speed * -1)) * (tmpx / tmpy));
	frctl->fract.x2 -= (((where == 1) ? speed : (speed * -1)) * (tmpx / tmpy));
	frctl->fract.y1 += (((where == 1) ? speed : (speed * -1)) * (tmpy / tmpx));
	frctl->fract.y2 -= (((where == 1) ? speed : (speed * -1)) * (tmpy / tmpx));*/
	mlx_destroy_image(mlx->mlxptr, mlx->img->ptr);
	mlx->img->ptr = mlx_new_image(mlx->mlxptr, X_SIZE, Y_SIZE);
	mlx->img->data = (int *)mlx_get_data_addr(mlx->img->ptr,
			&(mlx->img->bpp), &(mlx->img->linesize), &(mlx->img->endian));
	ft_mandelbrot(frctl);
	mlx_clear_window(mlx->mlxptr, mlx->win);
	mlx_put_image_to_window(mlx->mlxptr, mlx->win,
			frctl->mlx->img->ptr, 0, 0);
}

int		mouse_hook(int button, int x, int y, void *param)
{
	t_fractol	*frctl;

	frctl = (t_fractol *)param;
	return (0);
}

static void	ft_center_on_cursor(t_fractol *frctl)
{
	int		x;
	int		y;
	float	speed;
	float	tmpx;
	float	tmpy;

	speed = 0.1;
	x = frctl->status.x;
	y = frctl->status.y;
	tmpx = X_SCALING(frctl->fract.x2, frctl->fract.x1);
	tmpy = Y_SCALING(frctl->fract.y2, frctl->fract.y1);
	frctl->fract.x1 += ((x - X_SIZE / 2) / tmpx) * speed;
	frctl->fract.x2 += ((x - X_SIZE / 2) / tmpx) * speed;
	frctl->fract.y1 += ((y - Y_SIZE / 2) / tmpy) * speed;
	frctl->fract.y2 += ((y - Y_SIZE / 2) / tmpy) * speed;
/*	frctl->fract.x1 += ((x - X_SIZE / 2) * tmpx / tmpy) * speed;
	frctl->fract.x2 += ((x - X_SIZE / 2) * tmpx / tmpy) * speed;
	frctl->fract.y1 += ((y - Y_SIZE / 2) * tmpy / tmpx) * speed;
	frctl->fract.y2 += ((y - Y_SIZE / 2) * tmpy / tmpx) * speed;*/
}

void		ft_zoom_in(t_fractol *frctl)
{
	t_mlx	*mlx;
	float	tmpx;
	float	tmpy;

	mlx = frctl->mlx;
	tmpx = X_SCALING(frctl->fract.x2, frctl->fract.x1);
	tmpy = Y_SCALING(frctl->fract.y2, frctl->fract.y1);
/*	if (frctl->fract.x1 + 0.2 > frctl->fract.x2
		|| frctl->fract.y1 + 0.2 > frctl->fract.y2)
		return ;*/
	frctl->fract.x1 += (0.1 * (tmpx / tmpy));
	frctl->fract.x2 -= (0.1 * (tmpx / tmpy));
	frctl->fract.y1 += (0.1 * (tmpy / tmpx));
	frctl->fract.y2 -= (0.1 * (tmpy / tmpx));
	ft_center_on_cursor(frctl);
	mlx_destroy_image(mlx->mlxptr, mlx->img->ptr);
	mlx->img->ptr = mlx_new_image(mlx->mlxptr, X_SIZE, Y_SIZE);
	mlx->img->data = (int *)mlx_get_data_addr(mlx->img->ptr,
			&(mlx->img->bpp), &(mlx->img->linesize), &(mlx->img->endian));
	ft_mandelbrot(frctl);
	mlx_clear_window(mlx->mlxptr, mlx->win);
	mlx_put_image_to_window(mlx->mlxptr, mlx->win,
			frctl->mlx->img->ptr, 0, 0);
}

void		ft_zoom_out(t_fractol *frctl)
{
	t_mlx	*mlx;
	float	tmpx;
	float	tmpy;

	mlx = frctl->mlx;
	tmpx = X_SCALING(frctl->fract.x2, frctl->fract.x1);
	tmpy = Y_SCALING(frctl->fract.y2, frctl->fract.y1);
	frctl->fract.x1 -= (0.1 * (tmpx / tmpy));
	frctl->fract.x2 += (0.1 * (tmpx / tmpy));
	frctl->fract.y1 -= (0.1 * (tmpy / tmpx));
	frctl->fract.y2 += (0.1 * (tmpy / tmpx));
	ft_center_on_cursor(frctl);
	mlx_destroy_image(mlx->mlxptr, mlx->img->ptr);
	mlx->img->ptr = mlx_new_image(mlx->mlxptr, X_SIZE, Y_SIZE);
	mlx->img->data = (int *)mlx_get_data_addr(mlx->img->ptr,
			&(mlx->img->bpp), &(mlx->img->linesize), &(mlx->img->endian));
	ft_mandelbrot(frctl);
	mlx_clear_window(mlx->mlxptr, mlx->win);
	mlx_put_image_to_window(mlx->mlxptr, mlx->win,
			frctl->mlx->img->ptr, 0, 0);
}
