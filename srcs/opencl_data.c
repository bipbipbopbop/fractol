/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 17:08:56 by jhache            #+#    #+#             */
/*   Updated: 2018/04/04 16:01:42 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	*ft_deallocate_opencl(t_ocl **ocl, const char *debug_msg)
{
	int		i;

	if ((*ocl)->platforms)
		free((*ocl)->platforms);
	if ((*ocl)->device)
		clReleaseDevice((*ocl)->device);
	if ((*ocl)->context)
		clReleaseContext((*ocl)->context);
	if ((*ocl)->program)
		clReleaseProgram((*ocl)->program);
	if ((*ocl)->kernel)
		clReleaseKernel((*ocl)->kernel);
	if ((*ocl)->queue)
		clReleaseCommandQueue((*ocl)->queue);
	if ((*ocl)->info)
		ft_memdel(&(*ocl)->info);
	if (debug_msg)
		ft_putendl(debug_msg);
	ft_memdel((void **)ocl);
	return (NULL);
}

int		init_iter_array(t_fractol *frctl)
{
	cl_int			ret;
	size_t			array_size;

	array_size = sizeof(int) * (X_SIZE * Y_SIZE);
	frctl->fract.iter_array = clCreateBuffer(frctl->ocl->context,
			CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR | CL_MEM_HOST_READ_ONLY,
			array_size, NULL, &ret);
	if (frctl->fract.iter_array == NULL || ret < 0)
	{
		ft_putendl("error while creating the iteration array.");
		ft_deallocate(frctl, frctl->ptr);
		return (-1);
	}
	return (0);
}

int		ft_create_kernel(t_fractol *frctl, const char *path, size_t len)
{
	cl_int	ret[2];

	frctl->ocl->program = clCreateProgramWithBinary(
			frctl->ocl->context, 1, &frctl->ocl->device,
			&len, (const unsigned char **)&path, ret, &ret[1]);
	if (frctl->ocl->program == NULL || ret[0] < 0 || ret[1] < 0)
	{
		ft_printf("error while creating program.");
		ft_deallocate(frctl, frctl->ptr);
		return (-1);
	}
	if ((ret[0] = clBuildProgram(frctl->ocl->program, 1,
				&frctl->ocl->device, OPENCL_BUILD_FLAGS, NULL, NULL)) < 0)
	{
		ft_printf("error while building program.");
		ft_deallocate(frctl, frctl->ptr);
		return (ret[0]);
	}
	if ((ret[0] = clCreateKernelsInProgram(frctl->ocl->program,
					1, &frctl->ocl->kernel, NULL)) < 0)
	{
		ft_printf("error while creating kernels.");
		ft_deallocate(frctl, frctl->ptr);
	}
	return (ret[0]);
}

t_ocl	*ft_init_opencl(void)
{
	t_ocl	*ocl;
	cl_int	ret;

	if ((ocl = (t_ocl *)ft_memalloc(sizeof(t_ocl))) == NULL)
		return (NULL);
	if (!(ocl->platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id))))
		return (ft_deallocate_opencl(&ocl, NULL));
	ret = clGetPlatformIDs(1, ocl->platforms, NULL);
	if (ret < 0)
	{
		return (ft_deallocate_opencl(&ocl,
					"error while getting platform data."));
	}
	ret = clGetDeviceIDs(*ocl->platforms, CL_DEVICE_TYPE_GPU, 1,
			&ocl->device, NULL);
	if (ret < 0)
		return (ft_deallocate_opencl(&ocl, "error while getting device data."));
	ocl->context = clCreateContext(NULL, 1, &ocl->device, NULL, NULL, &ret);
	if (ret < 0)
		return (ft_deallocate_opencl(&ocl, "error while creating a context."));
	ocl->queue = clCreateCommandQueue(ocl->context, ocl->device, 0, &ret);
	if (ret < 0)
		return (ft_deallocate_opencl(&ocl, "error while creating the queue."));
	return (ocl);
}
