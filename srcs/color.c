/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 14:42:23 by jhache            #+#    #+#             */
/*   Updated: 2018/03/31 15:03:20 by jhache           ###   ########.fr       */
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
			tmp.byte[3] = 0;
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
			tmp.byte[3] = 0;
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

static void	compute_steps(char *pixel_ptr, t_fractol *frctl, int tmp)
{
	int		k;

	k = -1;
	if (tmp == 0 || tmp == 3)
	{
		while (++k < 3)
			pixel_ptr[k] = frctl->fract.clr.byte[k]
				+ ((0xFF - frctl->fract.clr.byte[k]) / 3);
	}
	else if (tmp == 1 || tmp == 4)
	{
		while (++k < 3)
			pixel_ptr[k] = frctl->fract.clr.byte[k];
	}
	else if (tmp == 2)
	{
		while (++k < 3)
			pixel_ptr[k] = frctl->fract.clr.byte[k]
				- (((int)frctl->fract.clr.byte[k] - 0xFF) / 1.8);
	}
}

void		color_steps(t_fractol *frctl, int *fract_array)
{
	int		i;
	char	*img_data;
	int		tmp;

	img_data = (char *)frctl->mlx->img->data;
	i = 0;
	while (i < X_SIZE * Y_SIZE * 4)
	{
		tmp = fract_array[i / 4] % 5;
		if (fract_array[i / 4] == frctl->fract.max_iter)
			frctl->mlx->img->data[i / 4] = 0;
		else
			compute_steps(&img_data[i], frctl, tmp);
		img_data[i + 3] = 0;
		i += 4;
	}
}
