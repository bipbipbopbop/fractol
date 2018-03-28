/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_event.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 13:07:02 by jhache            #+#    #+#             */
/*   Updated: 2018/03/28 13:47:08 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_change_max_iter(t_fractol *frctl, int sign)
{
	t_mlx		*mlx;
	size_t		work_size;
	int			i;

	work_size = X_SIZE * Y_SIZE;
	mlx = frctl->mlx;
	frctl->fract.max_iter += 50 * sign;
	mlx_destroy_image(mlx->mlxptr, mlx->img->ptr);
	mlx->img->ptr = mlx_new_image(mlx->mlxptr, X_SIZE, Y_SIZE);
	mlx->img->data = (int *)mlx_get_data_addr(mlx->img->ptr,
			&(mlx->img->bpp), &(mlx->img->linesize), &(mlx->img->endian));
	i = 0;
	while (g_fract[i].name != frctl->fract.name)
		++i;
	g_fract[i].fun_ptr(frctl, &work_size);
	mlx_clear_window(mlx->mlxptr, mlx->win);
	mlx_put_image_to_window(mlx->mlxptr, mlx->win,
			frctl->mlx->img->ptr, 0, 0);
	ft_printf("max_iter = %d\n", frctl->fract.max_iter);//A RETIRER ?
}

void		ft_reset(t_fractol *frctl)
{
	t_mlx	*mlx;
	size_t	work_size;

	work_size = X_SIZE * Y_SIZE;
	mlx = frctl->mlx;
	init_fract(frctl, frctl->fract.name);
	mlx_destroy_image(mlx->mlxptr, mlx->img->ptr);
	mlx->img->ptr = mlx_new_image(mlx->mlxptr, X_SIZE, Y_SIZE);
	mlx->img->data = (int *)mlx_get_data_addr(mlx->img->ptr,
			&(mlx->img->bpp), &(mlx->img->linesize), &(mlx->img->endian));
	ocl_mandelbrot(frctl, &work_size);
	mlx_clear_window(mlx->mlxptr, mlx->win);
	mlx_put_image_to_window(mlx->mlxptr, mlx->win,
			frctl->mlx->img->ptr, 0, 0);
}
