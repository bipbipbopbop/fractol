/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 18:05:52 by jhache            #+#    #+#             */
/*   Updated: 2018/03/27 18:54:49 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_frct_lst	g_fract[] = {
	{mandelbrot, &init_mandelbrot},
	{julia, &init_julia}};

void		init_fract(t_fractol *frctl, const char *name)
{
	t_fractal	*fract;
	int			i;

	fract = &frctl->fract;
	if (name != NULL && ft_strstr(name, "mandelbrot", STR) != NULL)
		fract->name = mandelbrot;
	else if (name != NULL && ft_strstr(name, "julia", STR) != NULL)
		fract->name = julia;
	else if (name != NULL)
	{
		ft_deallocate(frctl, frctl->ptr);
		ft_usage();
	}
	i = 0;
	while (fract->name != g_fract[i].name)
		++i;
	g_fract[i].f(fract);
	fract->max_iter = MAX_ITER;
//	PROCHAINEMENT: EXECUTER LA FRACTALE ICI
	printf("x1 = %f\nx2 = %f\ny1 = %f\ny2 = %f\n", fract->x1, fract->x2, fract->y1, fract->y2);
	printf("MADELBROTX1 = %f\nMADELBROTX2 = %f\nMADELBROTY1 = %f\nMADELBROTY2 = %f\n", MANDELBROTX1, MANDELBROTX2, MANDELBROTY1, MANDELBROTY2);//FONCTION INTERDITE
}

void		init_julia(t_fractal *fract)
{
	exit(666);
}

void		init_mandelbrot(t_fractal *fract)
{
	float	x_range;
	float	y_range;
	float	tmp;

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
