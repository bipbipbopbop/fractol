/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 04:06:01 by jhache            #+#    #+#             */
/*   Updated: 2018/04/04 19:26:03 by jhache           ###   ########.fr       */
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
	else if (name != NULL && ft_strcmp(name, "burning_ship") == 0)
		result = burning_ship;
	else if (name != NULL && ft_strcmp(name, "multibrot") == 0)
		result = multibrot;
	return (result);
}

void		ft_deallocate(t_fractol *frctl, void **anti_leaks_ptr)
{
	if (frctl->clrpick != NULL)
		ft_close_colorpicker(frctl->clrpick);
	if (frctl->mlx)
		ft_deallocate_mlx(&frctl->mlx, anti_leaks_ptr);
	if (frctl->ocl)
		ft_deallocate_opencl(&frctl->ocl, NULL);
	if (frctl->fract.iter_array != NULL)
		clReleaseMemObject(frctl->fract.iter_array);
	ft_memdel((void **)&frctl);
}

int			get_color(int color, void *param)
{
	t_fractol	*frctl;

	frctl = param;
	frctl->fract.clr.color = color;
	ocl_read_kernel_result(frctl);
	mlx_clear_window(frctl->mlx->mlxptr, frctl->mlx->win);
	mlx_put_image_to_window(frctl->mlx->mlxptr, frctl->mlx->win,
			frctl->mlx->img->ptr, 0, 0);
	return (0);
}

void		ocl_read_kernel_result(t_fractol *frctl)
{
	int		*tmp;
	cl_int	ret;
	int		i;

	i = 0;
	tmp = (int *)malloc(sizeof(int) * (X_SIZE * Y_SIZE));
	ret = clEnqueueReadBuffer(frctl->ocl->queue, frctl->fract.iter_array,
			CL_TRUE, 0, sizeof(int) * (X_SIZE * Y_SIZE), tmp, 0, NULL, NULL);
	if (ret < 0)
	{
		ft_putendl("error while reading kernel's result.\n");
		ft_deallocate(frctl, frctl->ptr);
		exit(-1);
	}
	while (g_clr_type[i].type != frctl->fract.clr_type)
		++i;
	g_clr_type[i].fun_ptr(frctl, tmp);
	ft_memdel((void **)&tmp);
}
