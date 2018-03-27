/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 18:00:23 by jhache            #+#    #+#             */
/*   Updated: 2018/03/27 18:22:14 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

cl_mem		ocl_mdbt_create_arg(t_fractol *frctl)
{
	cl_mem	inter;
	cl_int	ret;
	float	intermediate[5];

	intermediate[0] = X_SIZE;
	intermediate[1] = X_SCALING(frctl->fract.x2, frctl->fract.x1);
	intermediate[2] = frctl->fract.x1;
	intermediate[3] = Y_SCALING(frctl->fract.y2, frctl->fract.y1);
	intermediate[4] = frctl->fract.y1;
	inter = clCreateBuffer(frctl->ocl->context,
			CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR | CL_MEM_HOST_NO_ACCESS,
			sizeof(float) * 5, intermediate, &ret);
	if (inter == NULL || ret < 0)
	{
		ft_putendl("error while creating kernel arguments.");
		ft_deallocate(frctl, frctl->ptr);
		exit(-1);
	}
	return (inter);
}

void		ocl_mandelbrot(t_fractol *frctl, size_t *work_size)
{
	cl_int	ret;
	cl_mem	inter;

	inter = ocl_mdbt_create_arg(frctl);
	ret = clSetKernelArg(frctl->ocl->kernels[0], 0, sizeof(cl_mem),
			&frctl->fract.iter_array);
	ret |= clSetKernelArg(frctl->ocl->kernels[0], 1, sizeof(cl_mem),
			&inter);
	ret |= clSetKernelArg(frctl->ocl->kernels[0], 2, sizeof(int),
			&frctl->fract.max_iter);
	if (ret < 0)
	{
		ft_putendl("error while setting kernel arguments.");
		ft_deallocate(frctl, frctl->ptr);
		exit(-1);
	}
	if (clEnqueueNDRangeKernel(frctl->ocl->queue, frctl->ocl->kernels[0],
			1, NULL, work_size, NULL, 0, NULL, NULL) < 0)
	{
		ft_putendl("error while executing the kernel.");
		ft_deallocate(frctl, frctl->ptr);
		exit(-1);
	}
	clReleaseMemObject(inter);
	ocl_read_kernel_result(frctl);
}
/*
//int			ft_mandelbrot(t_fractol *frctl)
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
*/
