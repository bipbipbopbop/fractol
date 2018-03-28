/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 17:18:14 by jhache            #+#    #+#             */
/*   Updated: 2018/03/28 19:07:17 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		colorize(t_fractol *frctl, int *fract_array)
{
	int		i;
	int		*img_data;
	int		iter_max;
	int		tmp;

	iter_max = frctl->fract.max_iter;
	img_data = frctl->mlx->img->data;
	i = 0;
	while (i < X_SIZE * Y_SIZE)
	{
//	3 STATES : RED, BLUE, GREEN + black for fract -> non
/*		if (fract_array[i] < (iter_max / 3))
			img_data[i] = 0x00FF0000;
		else if (fract_array[i] < (iter_max / 3 * 2))
			img_data[i] = 0x0000FF00;
		else if (fract_array[i] < iter_max)
			img_data[i] = 0x0000FF;
		else if (fract_array[i] == iter_max)
			img_data[i] = 0;*/
//	FROM black for fract TO A PRIMARY COLOR -> si maxiter trop eleve, on voit rien
//		img_data[i] = 0xFF - (255 * ((float)fract_array[i] / iter_max));
//	STATES IS MODULO
		tmp = fract_array[i] % 5;
		if (fract_array[i] == iter_max)
			img_data[i] = 0;
		else if (tmp == 0)
			img_data[i] = 0x00AA1212;
		else if (tmp == 1)
			img_data[i] = 0x001BDEE5;
		else if (tmp == 2)
			img_data[i] = 0x006A15C0;
		else if (tmp == 3)
			img_data[i] = 0x0030DD30;
		else if (tmp == 4)
			img_data[i] = 0x00F9F14D;
//	DEGRADE D'1 COULEUR + STATES IS MODULO -> A FAIRE
//		else if (tmp == 0)
//			img_data[i] = frctl->fract.clr.color
/*		if (fract_array[i] == frctl->fract.max_iter)
			frctl->mlx->img->data[i] = 0x00FFFFFF;
		else
		frctl->mlx->img->data[i] = 0x0;*/
		++i;
	}
}

void		ocl_read_kernel_result(t_fractol *frctl)
{
	int		*tmp;
	cl_int	ret;

	tmp = (int *)malloc(sizeof(int) * X_SIZE * Y_SIZE);
	ret = clEnqueueReadBuffer(frctl->ocl->queue, frctl->fract.iter_array,
			CL_TRUE, 0, sizeof(int) * X_SIZE * Y_SIZE, tmp, 0, NULL, NULL);
	if (ret < 0)
	{
		ft_putendl("error while reading kernel's result.\n");
		ft_deallocate(frctl, frctl->ptr);
		exit(-1);
	}
	colorize(frctl, tmp);
	ft_memdel((void **)&tmp);
}
