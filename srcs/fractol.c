/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 02:12:39 by jhache            #+#    #+#             */
/*   Updated: 2018/03/07 06:05:11 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
/*
static void	initialize_fract(t_fractal *fract)
{
	fract->x1 = MANDELBROTX1;
	fract->x2 = MANDELBROTX2;
	fract->y1 = MANDELBROTY1;
	fract->y2 = MANDELBROTY2;
}

int			ft_mandelbrot(t_fractol *frctl, void *anti_leaks_ptr)
{
	int			i;
	int			img_ind;
	t_fractal	fract;
	float		tmp;

	(void)anti_leaks_ptr;
	img_ind = -1;
	initialize_fract(&fract);
	while (++img_ind < X_SIZE * Y_SIZE)
	{
		fract.c[0] = ((img_ind % X_SIZE) / X_ZOOM + fract.x1);
		fract.c[1] = ((img_ind / X_SIZE) / Y_ZOOM + fract.y1);
		fract.z[0] = 0;
		fract.z[1] = 0;
		i = 0;
//		while ((fract.z[0] * fract.z[0] - fract.z[1] * fract.z[1] + fract.c[0])
//			< 4 && i < MAX_ITER)
		while ((fract.z[0] * fract.z[0] + fract.z[1] * fract.z[1])
			< 4 && i < MAX_ITER)
		{
			tmp = fract.z[0];
			fract.z[0] = (fract.z[0] * fract.z[0]
				- fract.z[1] * fract.z[1] + fract.c[0]);
			fract.z[1] = 2 * fract.z[1] * tmp + fract.c[1];
			++i;
		}
		if (i == MAX_ITER)
			frctl->mlx->img->data[img_ind] = 0x00FFFFFF;
	}
	return (0);
}
*/

int			ft_mandelbrot(t_fractol *frctl, void *anti_leaks_ptr)
{
	int			i;
	int			img_ind;
	t_fractal	fract;
	float		tmp;

	(void)anti_leaks_ptr;
	img_ind = -1;
	while (++img_ind < X_SIZE * Y_SIZE)
	{
		fract.c[0] = img_ind % X_SIZE;
		fract.c[1] = img_ind / X_SIZE;
		fract.z[0] = 0;
		fract.z[1] = 0;
		i = 0;
		while ((fract.z[0] * fract.z[0] + fract.z[1] * fract.z[1])
			< 4 && i < MAX_ITER)
		{
			tmp = fract.z[0];
			fract.z[0] = (fract.z[0] * fract.z[0]
				- fract.z[1] * fract.z[1] + fract.c[0]);
			fract.z[1] = 2 * fract.z[1] * tmp + fract.c[1];
			++i;
		}
		if (i == MAX_ITER)
			frctl->mlx->img->data[img_ind] = 0x00FFFFFF;
	}
	return (0);
}
