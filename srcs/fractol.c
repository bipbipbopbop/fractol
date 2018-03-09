/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 02:12:39 by jhache            #+#    #+#             */
/*   Updated: 2018/03/09 13:08:25 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_init_fract(t_fractol *frctl, const char *name)
{
	t_fractal	*fract;

	fract = &frctl->fract;
	if (ft_strstr(name, "mandelbrot", STR) != NULL)
		fract->name = mandelbrot;
	else if (ft_strstr(name, "julia", STR) != NULL)
		fract->name = julia;
	else
	{
		ft_deallocate(frctl, frctl->ptr);
		ft_usage();
	}
	fract->x1 = MANDELBROTX1;
	fract->x2 = MANDELBROTX2;
	fract->y1 = MANDELBROTY1;
	fract->y2 = MANDELBROTY2;
}

int			ft_mandelbrot(t_fractol *frctl)
{
	int			iter;
	int			img_ind;
	t_fractal	fract;
	float		tmp;

	img_ind = -1;
	fract = frctl->fract;
	while (++img_ind < X_SIZE * Y_SIZE)
	{
		fract.c[0] = ((img_ind % X_SIZE)
					/ X_SCALING(fract.x2, fract.x1) + fract.x1);
		fract.c[1] = ((img_ind / X_SIZE)
					/ Y_SCALING(fract.y2, fract.y1) + fract.y1);
		fract.z[0] = 0;
		fract.z[1] = 0;
		iter = 0;
		while ((fract.z[0] * fract.z[0] + fract.z[1] * fract.z[1])
			< 4 && iter < MAX_ITER)
		{
			tmp = fract.z[0];
			fract.z[0] = (fract.z[0] * fract.z[0]
				- fract.z[1] * fract.z[1] + fract.c[0]);
			fract.z[1] = 2 * fract.z[1] * tmp + fract.c[1];
			++iter;
		}
		if (iter == MAX_ITER)
			frctl->mlx->img->data[img_ind] = 0x00FFFFFF;
	}
	return (0);
}
