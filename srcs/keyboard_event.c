/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_event.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 13:07:02 by jhache            #+#    #+#             */
/*   Updated: 2018/03/28 19:08:06 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_change_max_iter(t_fractol *frctl, int sign)
{
	t_mlx		*mlx;
	size_t		work_size;
	int			i;

	work_size = X_SIZE * Y_SIZE;
	mlx = frctl->mlx;
	frctl->fract.max_iter += 20 * sign;
	i = 0;
	while (g_fract[i].name != frctl->fract.name)
		++i;
	g_fract[i].fun_ptr(frctl, &work_size);
	mlx_clear_window(mlx->mlxptr, mlx->win);
	mlx_put_image_to_window(mlx->mlxptr, mlx->win,
			frctl->mlx->img->ptr, 0, 0);
	ft_printf("max_iter = %d\n", frctl->fract.max_iter);//A RETIRER ?
}

void		ft_reset(t_fractol *frctl)
{
	t_mlx	*mlx;
	size_t	work_size;
	int		i;

	work_size = X_SIZE * Y_SIZE;
	mlx = frctl->mlx;
	init_fract(frctl, frctl->fract.name);
	i = 0;
	while (g_fract[i].name != frctl->fract.name)
		++i;
	g_fract[i].fun_ptr(frctl, &work_size);
	mlx_clear_window(mlx->mlxptr, mlx->win);
	mlx_put_image_to_window(mlx->mlxptr, mlx->win,
			frctl->mlx->img->ptr, 0, 0);
}
