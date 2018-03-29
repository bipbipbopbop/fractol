/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 17:18:14 by jhache            #+#    #+#             */
/*   Updated: 2018/03/29 23:14:24 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		color_reverse_gradient(t_fractol *frctl, int *fract_array)
{
	int		i;
	int		k;
	int		iter_max;
	t_color	tmp;

	iter_max = frctl->fract.max_iter;
	i = 0;
	while (i < X_SIZE * Y_SIZE)
	{
		if (fract_array[i] == iter_max)
			frctl->mlx->img->data[i] = 0;
		else
		{
			k = -1;
			while (++k < 3)
				tmp.byte[k] = frctl->fract.clr.byte[k]
					- (frctl->fract.clr.byte[k]
						* ((float)fract_array[i] / iter_max));
			frctl->mlx->img->data[i] = tmp.color;
		}
		++i;
	}
}

void		color_gradient(t_fractol *frctl, int *fract_array)
{
	int		i;
	int		k;
	int		iter_max;
	t_color	tmp;

	iter_max = frctl->fract.max_iter;
	i = 0;
	while (i < X_SIZE * Y_SIZE)
	{
		if (fract_array[i] == iter_max)
			frctl->mlx->img->data[i] = 0;
		else
		{
			k = -1;
			while (++k < 3)
				tmp.byte[k] = frctl->fract.clr.byte[k]
					* ((float)fract_array[i] / iter_max);
			frctl->mlx->img->data[i] = tmp.color;
		}
		++i;
	}
}
void		color_random(t_fractol *frctl, int *fract_array)
{
	int		i;
	int		*img_data;
	int		iter_max;

	iter_max = frctl->fract.max_iter;
	img_data = frctl->mlx->img->data;
	i = 0;
	while (i < X_SIZE * Y_SIZE)
	{
		if (fract_array[i] == iter_max)
			img_data[i] = 0;
		else
			img_data[i] = (int)((frctl->fract.clr.color *
						((float)fract_array[i] / iter_max)))
						^ frctl->fract.clr.color;
		++i;
	}
}

void		color_steps(t_fractol *frctl, int *fract_array)
{
	int		i;
	int		k;
	char	*img_data;
	int		tmp;

	img_data = (char *)frctl->mlx->img->data;
	i = 0;
	while (i < X_SIZE * Y_SIZE * 4)
	{
		tmp = fract_array[i / 4] % 5;
		k = -1;
		while (++k < 3)
		{
			if (fract_array[i / 4] == frctl->fract.max_iter)
				img_data[i + k] = 0;
			else if (tmp == 0 || tmp == 3)
				img_data[i + k] = frctl->fract.clr.byte[k]
					+ ((0xFF - frctl->fract.clr.byte[k]) / 3);
			else if (tmp == 1 || tmp == 4)
				img_data[i + k] = frctl->fract.clr.byte[k];
			else if (tmp == 2)
				img_data[i + k] = frctl->fract.clr.byte[k]
					- (((int)frctl->fract.clr.byte[k] - 0xFF) / 1.8);
		}
		i += 4;
	}
}

void		ocl_read_kernel_result(t_fractol *frctl)
{
	int		*tmp;
	cl_int	ret;
	int		i;

	i = 0;
	tmp = (int *)malloc(sizeof(int) * X_SIZE * Y_SIZE);
	ret = clEnqueueReadBuffer(frctl->ocl->queue, frctl->fract.iter_array,
			CL_TRUE, 0, sizeof(int) * X_SIZE * Y_SIZE, tmp, 0, NULL, NULL);
	if (ret < 0)
	{
		ft_putendl("error while reading kernel's result.\n");
		ft_deallocate(frctl, frctl->ptr);
		exit(-1);
	}
	while (g_clr_type[i].type != frctl->fract.clr_type)
		++i;
	g_clr_type[i].fun_ptr(frctl, tmp);
	ft_memdel((void **)&tmp);
}
