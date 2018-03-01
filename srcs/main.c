/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 13:07:24 by jhache            #+#    #+#             */
/*   Updated: 2018/03/01 13:57:18 by jhache           ###   ########.fr       */
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

int			main(int ac, char **av)
{
	t_fractol	*frctl;

	if (ac != 2)
		ft_usage();
	if (!(frctl = (t_fractol *)malloc(sizeof(t_fractol))))
		ft_error("malloc", NULL);
	if (!(frctl->mlx = ft_init_mlx())
		|| !(frctl->ocl = ft_init_opencl()))
		ft_deallocate(frctl);

	return (0);
}
