/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 13:35:27 by jhache            #+#    #+#             */
/*   Updated: 2018/04/02 17:13:17 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static cl_mem	ocl_julia_create_arg(t_fractol *frctl)
{
	cl_mem	inter;
	cl_int	ret;
	float	intermediate[7];

	intermediate[0] = (float)frctl->status.cursor_pos_param[0] / X_SIZE;
	intermediate[1] = (float)frctl->status.cursor_pos_param[1] / Y_SIZE;
	intermediate[2] = X_SIZE;
	intermediate[3] = X_SCALING(frctl->fract.x2, frctl->fract.x1);
	intermediate[4] = Y_SCALING(frctl->fract.y2, frctl->fract.y1);
	intermediate[5] = frctl->fract.x1;
	intermediate[6] = frctl->fract.y1;
	inter = clCreateBuffer(frctl->ocl->context,
			CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR | CL_MEM_HOST_NO_ACCESS,
			sizeof(float) * 7, intermediate, &ret);
	if (inter == NULL || ret < 0)
	{
		ft_putendl("error while creating kernel arguments.");
		ft_deallocate(frctl, frctl->ptr);
		exit(-1);
	}
	return (inter);
}

void			ocl_julia(t_fractol *frctl, size_t *work_size)
{
	cl_int	ret;
	cl_mem	inter;

	inter = ocl_julia_create_arg(frctl);
	ret = clSetKernelArg(frctl->ocl->kernels[JULIA], 0, sizeof(cl_mem),
			&frctl->fract.iter_array);
	ret |= clSetKernelArg(frctl->ocl->kernels[JULIA], 1, sizeof(cl_mem),
			&inter);
	ret |= clSetKernelArg(frctl->ocl->kernels[JULIA], 2, sizeof(int),
			&frctl->fract.max_iter);
	if (ret < 0)
	{
		ft_putendl("error while setting kernel arguments.");
		ft_deallocate(frctl, frctl->ptr);
		exit(-1);
	}
	if (clEnqueueNDRangeKernel(frctl->ocl->queue, frctl->ocl->kernels[JULIA],
			1, NULL, work_size, NULL, 0, NULL, NULL) < 0)
	{
		ft_putendl("error while executing the kernel.");
		ft_deallocate(frctl, frctl->ptr);
		exit(-1);
	}
	clReleaseMemObject(inter);
	ocl_read_kernel_result(frctl);
}
