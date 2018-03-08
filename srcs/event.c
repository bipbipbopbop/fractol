/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:14:30 by jhache            #+#    #+#             */
/*   Updated: 2018/03/08 17:51:55 by jhache           ###   ########.fr       */
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
	float	tmp;

	mlx = frctl->mlx;
	tmp = (frctl->fract.x2 - frctl->fract.x1)
		/ (frctl->fract.y2 - frctl->fract.y1);
	frctl->fract.x1 += (((where == 1) ? 0.1 : -0.1) * tmp);
	frctl->fract.x2 -= (((where == 1) ? 0.1 : -0.1) * tmp);
	tmp = (frctl->fract.y2 - frctl->fract.y1)
		/ (frctl->fract.x2 - frctl->fract.x1);
	frctl->fract.y1 += (((where == 1) ? 0.1 : -0.1) * tmp);
	frctl->fract.y2 -= (((where == 1) ? 0.1 : -0.1) *tmp);
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
