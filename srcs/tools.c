/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 04:06:01 by jhache            #+#    #+#             */
/*   Updated: 2018/03/27 18:48:36 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_deallocate(t_fractol *frctl, void **anti_leaks_ptr)
{
	if (frctl->mlx)
		ft_deallocate_mlx(&frctl->mlx, anti_leaks_ptr);
	if (frctl->ocl)
		ft_deallocate_opencl(&frctl->ocl, NULL);
	if (frctl->fract.iter_array != NULL)
		clReleaseMemObject(frctl->fract.iter_array);
	ft_memdel((void **)&frctl);
}

void		ocl_read_kernel_result(t_fractol *frctl)
{
	int		i;
	int		*tmp;
	cl_int	ret;

	tmp = (int *)malloc(sizeof(int) * X_SIZE * Y_SIZE);
	ret = clEnqueueReadBuffer(frctl->ocl->queue, frctl->fract.iter_array,
								 CL_TRUE, 0, sizeof(int) * X_SIZE * Y_SIZE,
								 tmp, 0, NULL, NULL);
	if (ret < 0)
	{
		ft_putendl("error while reading kernel's result.\n");
		ft_deallocate(frctl, frctl->ptr);
		exit(-1);
	}
	i = 0;
	while (i < X_SIZE * Y_SIZE)
	{
		if (tmp[i] == MAX_ITER)
			frctl->mlx->img->data[i] = 0x00FFFFFF;
		++i;
	}
	ft_memdel((void **)&tmp);
}

void		ft_reset(t_fractol *frctl)
{
	t_mlx	*mlx;
	size_t	work_size;

	work_size = X_SIZE * Y_SIZE;
	mlx = frctl->mlx;
	init_fract(frctl, NULL);
	ocl_mandelbrot(frctl, &work_size);//A SUPPRIMER QUAND init_fract LE FERA
	mlx_destroy_image(mlx->mlxptr, mlx->img->ptr);
	mlx->img->ptr = mlx_new_image(mlx->mlxptr, X_SIZE, Y_SIZE);
	mlx->img->data = (int *)mlx_get_data_addr(mlx->img->ptr,
			&(mlx->img->bpp), &(mlx->img->linesize), &(mlx->img->endian));
	ocl_mandelbrot(frctl, &work_size);
	mlx_clear_window(mlx->mlxptr, mlx->win);
	mlx_put_image_to_window(mlx->mlxptr, mlx->win,
			frctl->mlx->img->ptr, 0, 0);
}
