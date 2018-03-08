/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 17:08:51 by jhache            #+#    #+#             */
/*   Updated: 2018/03/08 15:36:26 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_deallocate_mlx(t_mlx **mlx, void **anti_leaks_ptr)
{
	if ((*mlx)->clrpick != NULL)
		ft_close_colorpicker((*mlx)->clrpick);
	if ((*mlx)->img)
	{
		if ((*mlx)->img->data)
			mlx_destroy_image((*mlx)->mlxptr, (*mlx)->img->ptr);
		ft_memdel((void **)&(*mlx)->img);
	}
	if ((*mlx)->win)
		mlx_destroy_window((*mlx)->mlxptr, (*mlx)->win);
	*anti_leaks_ptr = (*mlx)->mlxptr;
	ft_memdel((void **)mlx);
}

t_mlx		*ft_init_mlx(void **anti_leaks_ptr)
{
	t_mlx	*mlx;
	int		i;

	if (!(mlx = (t_mlx *)ft_memalloc(sizeof(t_mlx))))
		return (NULL);
	if (!(mlx->mlxptr = mlx_init())
		|| !(mlx->win = mlx_new_window(mlx->mlxptr, X_SIZE, Y_SIZE, WIN_NAME))
		|| !(mlx->img = (t_img *)malloc(sizeof(t_img)))
		|| !(mlx->img->ptr = mlx_new_image(mlx->mlxptr, X_SIZE, Y_SIZE))
		|| !(mlx->img->data = (int *)mlx_get_data_addr(mlx->img->ptr,
				&(mlx->img->bpp), &(mlx->img->linesize), &(mlx->img->endian)))/*
		|| !(mlx->clrpick = ft_colorpicker(field->mlx, &FUNCTION, (void *)mlx, "Color Picker"))*/)
	{
		ft_deallocate_mlx(&mlx, anti_leaks_ptr);
		return (NULL);
	}
// Pour color_picker, il faudrai l'initialiser aileurs, genre pour pouvoir choisir
// le pointeur sur fonction que je veux
	return (mlx);
}
