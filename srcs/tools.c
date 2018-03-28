/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 04:06:01 by jhache            #+#    #+#             */
/*   Updated: 2018/03/28 13:50:42 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_name		ft_select_fract(const char *name)
{
	t_name	result;

	result = none;
	if (name != NULL && ft_strcmp(name, "mandelbrot") == 0)
		result = mandelbrot;
	else if (name != NULL && ft_strcmp(name, "julia") == 0)
		result = julia;
	return (result);
}

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
			CL_TRUE, 0, sizeof(int) * X_SIZE * Y_SIZE, tmp, 0, NULL, NULL);
	if (ret < 0)
	{
		ft_putendl("error while reading kernel's result.\n");
		ft_deallocate(frctl, frctl->ptr);
		exit(-1);
	}
	i = 0;
	while (i < X_SIZE * Y_SIZE)
	{
		if (tmp[i] == frctl->fract.max_iter)
			frctl->mlx->img->data[i] = 0x00FFFFFF;
		++i;
	}
	ft_memdel((void **)&tmp);
}
