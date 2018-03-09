/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 13:07:24 by jhache            #+#    #+#             */
/*   Updated: 2018/03/09 14:25:20 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_usage(void)
{
	ft_printf("usage: ./fractol \"fractal_name\"\n-> mandelbrot\n-> julia\n");
	exit(0);
}

void		ft_error(const char *perror_msg, const char *message)
{
	if (perror_msg != NULL)
	{
		perror(perror_msg);
		ft_putchar('\n');
	}
	if (message != NULL)
		ft_putendl(message);
	exit(1);
}

void		ft_deallocate(t_fractol *frctl, void **anti_leaks_ptr)
{
	if (frctl->mlx)
		ft_deallocate_mlx(&frctl->mlx, anti_leaks_ptr);
	if (frctl->ocl)
		ft_deallocate_opencl(&frctl->ocl, NULL);
	ft_memdel((void **)&frctl);
}

int			main(int ac, char **av)
{
	t_fractol	*frctl;
	void		*anti_leaks_ptr;

	if (ac != 2)
		ft_usage();
	if (!(frctl = (t_fractol *)ft_memalloc(sizeof(t_fractol))))
		ft_error("malloc", NULL);
	frctl->ptr = &anti_leaks_ptr;
	ft_init_fract(frctl, av[1]);
	if (!(frctl->mlx = ft_init_mlx(&anti_leaks_ptr))
		|| !(frctl->ocl = ft_init_opencl())
		|| ft_create_kernels(frctl->ocl, KERNEL_PATH) != 0)
		ft_deallocate(frctl, &anti_leaks_ptr);
	ft_mandelbrot(frctl);
	mlx_put_image_to_window(frctl->mlx->mlxptr,
		frctl->mlx->win, frctl->mlx->img->ptr, 0, 0);
	mlx_key_hook(frctl->mlx->win, &key_hook, (void *)frctl);
	mlx_mouse_hook(frctl->mlx->win, &mouse_hook, (void *)frctl);
	mlx_hook(frctl->mlx->win, MOTIONNOTIFY, POINTERMOTIONMASK,
		&ft_get_cursor_pos, (void *)frctl);
	mlx_hook(frctl->mlx->win, BUTTONPRESS, BUTTONPRESSMASK,
		&ft_mouse_event, (void *)frctl);
	mlx_loop(frctl->mlx->mlxptr);
	return (0);
}
