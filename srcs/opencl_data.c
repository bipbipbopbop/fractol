/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 17:08:56 by jhache            #+#    #+#             */
/*   Updated: 2018/03/27 18:12:26 by jhache           ###   ########.fr       */
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
	if ((*ocl)->kernels)
	{
		i = -1;
		while (++i < KERNELS_NB && (*ocl)->kernels[i])
			clReleaseKernel((*ocl)->kernels[i]);
		ft_memdel((void **)&(*ocl)->kernels);
		}
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

// 1: essayer CL_MEM_WRITE_ONLY
 	frctl->fract.iter_array = clCreateBuffer(frctl->ocl->context,
			CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR | CL_MEM_HOST_READ_ONLY,
			sizeof(int) * X_SIZE * Y_SIZE, NULL, &ret);
	if (frctl->fract.iter_array == NULL || ret < 0)
	{
		ft_putendl("error while creating the iteration array.");
		ft_deallocate(frctl, frctl->ptr);
		return (-1);
	}
	return (0);
}

int		ft_create_kernels(t_ocl *ocl, const char *path)
{
	size_t	len;
	cl_int	ret;
	cl_int	err;

	len = ft_strlen(path);
	ocl->program = clCreateProgramWithBinary(ocl->context, 1, &ocl->device,
		&len, (const unsigned char **)&path, &ret, &err);
	if (ocl->program == NULL || ret < 0 || err < 0)
	{
		ft_deallocate_opencl(&ocl, "error while creating program.");
		return ((ret < 0) ? ret : -1);
	}
	if ((ret = clBuildProgram(ocl->program, 1,
				&ocl->device, OPENCL_BUILD_FLAGS, NULL, NULL)) < 0)
	{
		ft_deallocate_opencl(&ocl, "error while building program.");
		return (ret);
	}
//	il faut tester dans quel sens je recois les kernels, et attribuer une macro
//	pour chaque index du tableau kernels
	if (!(ocl->kernels = (cl_kernel *)ft_memalloc(sizeof(cl_kernel)
				* KERNELS_NB)) || (ret = clCreateKernelsInProgram(
				ocl->program, KERNELS_NB, ocl->kernels, NULL)) < 0)
	{
		ft_deallocate_opencl(&ocl, "error while creating kernels.");
		return (ret);
	}
	return (0);
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
		return (ft_deallocate_opencl(&ocl,
				"error while getting platform data."));
	ret = clGetDeviceIDs(*ocl->platforms, CL_DEVICE_TYPE_GPU,
		1, &ocl->device, NULL);
	if (ret < 0)
		return (ft_deallocate_opencl(&ocl, "error while getting device data."));
	ocl->context = clCreateContext(NULL, 1, &ocl->device, NULL, NULL, &ret);
	if (ret < 0)
		return (ft_deallocate_opencl(&ocl, "error while creating a context."));
	ocl->queue = clCreateCommandQueue(ocl->context, ocl->device, 0, &ret);
	if (ret < 0)
		return (ft_deallocate_opencl(&ocl,
				"error while creating a command queue."));
	return (ocl);
}
