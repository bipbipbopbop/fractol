/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 04:06:01 by jhache            #+#    #+#             */
/*   Updated: 2018/03/28 17:18:30 by jhache           ###   ########.fr       */
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
