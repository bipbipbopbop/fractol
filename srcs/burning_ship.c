/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 19:00:18 by jhache            #+#    #+#             */
/*   Updated: 2018/04/04 16:07:10 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static cl_mem	ocl_burns_create_arg(t_fractol *frctl)
{
	cl_mem	inter;
	cl_int	ret;
	float	intermediate[5];

	if (((frctl->ocl->kernel == 0) ?
				ft_create_kernel(frctl, "./objs/burning_ship.clbin",
					ft_strlen("./objs/burning_ship.clbin")) : 0) < 0)
		exit(-1);
	intermediate[0] = X_SIZE;
	intermediate[1] = X_SCALING(frctl->fract.x2, frctl->fract.x1);
	intermediate[2] = Y_SCALING(frctl->fract.y2, frctl->fract.y1);
	intermediate[3] = frctl->fract.x1;
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

void			ocl_burning_ship(t_fractol *frctl, size_t *work_size)
{
	cl_int	ret;
	cl_mem	inter;

	inter = ocl_burns_create_arg(frctl);
	ret = clSetKernelArg(frctl->ocl->kernel, 0, sizeof(cl_mem),
			&frctl->fract.iter_array);
	ret |= clSetKernelArg(frctl->ocl->kernel, 1, sizeof(cl_mem),
			&inter);
	ret |= clSetKernelArg(frctl->ocl->kernel, 2, sizeof(int),
			&frctl->fract.max_iter);
	if (ret < 0)
	{
		ft_putendl("error while setting kernel arguments.");
		ft_deallocate(frctl, frctl->ptr);
		exit(-1);
	}
	if (clEnqueueNDRangeKernel(frctl->ocl->queue, frctl->ocl->kernel,
			1, NULL, work_size, NULL, 0, NULL, NULL) < 0)
	{
		ft_putendl("error while executing the kernel.");
		ft_deallocate(frctl, frctl->ptr);
		exit(-1);
	}
	clReleaseMemObject(inter);
	ocl_read_kernel_result(frctl);
}
