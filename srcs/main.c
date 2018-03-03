/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 13:07:24 by jhache            #+#    #+#             */
/*   Updated: 2018/03/03 19:45:05 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_usage(void)
{
	ft_printf("usage: \n");
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

void		ft_deallocate(t_fractol *frctl)
{
	if (frctl->mlx)
		ft_deallocate_mlx(&frctl->mlx);
	if (frctl->ocl)
		ft_deallocate_opencl(&frctl->ocl, NULL);
	ft_memdel((void **)&frctl);
}

int			main(int ac, char **av)
{
	t_fractol	*frctl;

	if (ac != 1)
		ft_usage();
	if (!(frctl = (t_fractol *)ft_memalloc(sizeof(t_fractol))))
		ft_error("malloc", NULL);
	if (!(frctl->mlx = ft_init_mlx())
		|| !(frctl->ocl = ft_init_opencl())
		|| ft_create_kernels(frctl->ocl, KERNEL_PATH) != 0)
		ft_deallocate(frctl);
	if (frctl)
		ft_deallocate(frctl);
	else
		ft_printf("ERROR\n");
	ft_printf("fin\n");
	return (0);
}
