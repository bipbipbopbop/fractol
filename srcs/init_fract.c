/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 18:05:52 by jhache            #+#    #+#             */
/*   Updated: 2018/04/04 20:41:46 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		init_fract(t_fractol *frctl, t_name fractale_name)
{
	t_fractal	*fract;
	int			i;
	size_t		work_size;
	char		*path;

	work_size = X_SIZE * Y_SIZE;
	fract = &frctl->fract;
	frctl->fract.name = fractale_name;
	i = 0;
	while (fract->name != g_fract[i].name)
		++i;
	fract->max_iter = MAX_ITER;
	g_fract[i].init_ptr(fract);
	g_fract[i].fun_ptr(frctl, &work_size);
	ft_printf("max_iter = %d\n", fract->max_iter);
}

void		init_julia(t_fractal *fract)
{
	t_real	x_range;
	t_real	y_range;
	t_real	tmp;

	x_range = JULIAX2 - JULIAX1;
	y_range = JULIAY2 - JULIAY1;
	if ((X_SIZE / x_range) > (Y_SIZE / y_range))
	{
		tmp = (Y_SIZE * x_range / y_range);
		fract->y1 = JULIAY1;
		fract->y2 = JULIAY2;
		fract->x1 = JULIAX1 - (((X_SIZE - tmp) / (tmp / x_range)) / 2);
		fract->x2 = JULIAX2 + (((X_SIZE - tmp) / (tmp / x_range)) / 2);
	}
	else
	{
		tmp = (X_SIZE * y_range / x_range);
		fract->y1 = JULIAY1 - (((Y_SIZE - tmp) / (tmp / y_range)) / 2);
		fract->y2 = JULIAY2 + (((Y_SIZE - tmp) / (tmp / y_range)) / 2);
		fract->x1 = JULIAX1;
		fract->x2 = JULIAX2;
	}
}

void		init_mandelbrot(t_fractal *fract)
{
	t_real	x_range;
	t_real	y_range;
	t_real	tmp;

	x_range = MANDELBROTX2 - MANDELBROTX1;
	y_range = MANDELBROTY2 - MANDELBROTY1;
	if ((X_SIZE / x_range) > (Y_SIZE / y_range))
	{
		tmp = (Y_SIZE * x_range / y_range);
		fract->y1 = MANDELBROTY1;
		fract->y2 = MANDELBROTY2;
		fract->x1 = MANDELBROTX1 - (((X_SIZE - tmp) / (tmp / x_range)) / 2);
		fract->x2 = MANDELBROTX2 + (((X_SIZE - tmp) / (tmp / x_range)) / 2);
	}
	else
	{
		tmp = (X_SIZE * y_range / x_range);
		fract->y1 = MANDELBROTY1 - (((Y_SIZE - tmp) / (tmp / y_range)) / 2);
		fract->y2 = MANDELBROTY2 + (((Y_SIZE - tmp) / (tmp / y_range)) / 2);
		fract->x1 = MANDELBROTX1;
		fract->x2 = MANDELBROTX2;
	}
}

void		init_burning_ship(t_fractal *fract)
{
	t_real	x_range;
	t_real	y_range;
	t_real	tmp;

	x_range = BURNINGSX2 - BURNINGSX1;
	y_range = BURNINGSY2 - BURNINGSY1;
	if ((X_SIZE / x_range) > (Y_SIZE / y_range))
	{
		tmp = (Y_SIZE * x_range / y_range);
		fract->y1 = BURNINGSY1;
		fract->y2 = BURNINGSY2;
		fract->x1 = BURNINGSX1 - (((X_SIZE - tmp) / (tmp / x_range)) / 2);
		fract->x2 = BURNINGSX2 + (((X_SIZE - tmp) / (tmp / x_range)) / 2);
	}
	else
	{
		tmp = (X_SIZE * y_range / x_range);
		fract->y1 = BURNINGSY1 - (((Y_SIZE - tmp) / (tmp / y_range)) / 2);
		fract->y2 = BURNINGSY2 + (((Y_SIZE - tmp) / (tmp / y_range)) / 2);
		fract->x1 = BURNINGSX1;
		fract->x2 = BURNINGSX2;
	}
}

void		init_multibrot(t_fractal *fract)
{
	t_real	x_range;
	t_real	y_range;
	t_real	tmp;

	x_range = MULTIBROTX2 - MULTIBROTX1;
	y_range = MULTIBROTY2 - MULTIBROTY1;
	if ((X_SIZE / x_range) > (Y_SIZE / y_range))
	{
		tmp = (Y_SIZE * x_range / y_range);
		fract->y1 = MULTIBROTY1;
		fract->y2 = MULTIBROTY2;
		fract->x1 = MULTIBROTX1 - (((X_SIZE - tmp) / (tmp / x_range)) / 2);
		fract->x2 = MULTIBROTX2 + (((X_SIZE - tmp) / (tmp / x_range)) / 2);
	}
	else
	{
		tmp = (X_SIZE * y_range / x_range);
		fract->y1 = MULTIBROTY1 - (((Y_SIZE - tmp) / (tmp / y_range)) / 2);
		fract->y2 = MULTIBROTY2 + (((Y_SIZE - tmp) / (tmp / y_range)) / 2);
		fract->x1 = MULTIBROTX1;
		fract->x2 = MULTIBROTX2;
	}
}
