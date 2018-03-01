/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 13:57:33 by jhache            #+#    #+#             */
/*   Updated: 2018/03/01 14:33:57 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_deallocate_mlx(t_mlx *mlx)
{
	if (mlx->clrpick)
		ft_close_colorpicker(mlx->clrpick);
	if (mlx->img)
	{
		if (mlx->img->data)
			mlx_destroy_image(mlx->mlxptr, mlx->img->ptr);
		ft_memdel(mlx->img);
	}
	if (mlx->win)
		mlx_destroy_window(mlx->mlxptr, mlx->win);
	ft_memdel(mlx);
}

t_mlx		*ft_init_mlx(void)
{
	t_mlx	*mlx;
	int		i;

	if (!(mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		return (NULL);
	mlx = ft_bzero((char *)mlx, sizeof(mlx));
	if (!(mlx->mlxptr = mlx_init())
		|| !(mlx->win = mlx_new_window(mlx->mlxptr, X_SIZE, Y_SIZE, WIN_NAME))
		|| !(mlx->img = (t_img *)malloc(sizeof(t_img)))
		|| !(mlx->img->ptr = mlx_new_image(mlx->mlxptr, X_SIZE, Y_SIZE))
		|| !(mlx->img->data = (int *)mlx_get_data_addr(mlx->img->ptr,
				&(mlx->img->bpp), &(mlx->img->linesize), &(mlx->img->endian)))/*
		|| !(mlx->clrpick = ft_colorpicker(field->mlx, &FUNCTION, (void *)mlx, "Color Picker"))*/)
	{
		ft_deallocate_mlx(mlx);
		return (NULL);
	}
// Pour color_picker, il faudrai l'initialiser aileurs, genre pour pouvoir choisir
// le pointeur sur fonction que je veux
	return (mlx);
}
