/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 13:08:35 by jhache            #+#    #+#             */
/*   Updated: 2018/03/27 18:48:57 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
#  else
#  include <CL/cl.h>
# endif
# include "libft.h"
# include "file_handling.h"
# include "ft_colorpicker.h"
# include "mlx.h"
# include "mlx_keycode.h"
# include <stdio.h>
# include <errno.h>


# define KERNELS_NB 2
# define KERNEL_PATH "./kernels/mandelbrot.clbin"
# define OPENCL_BUILD_FLAGS "-Werror"

# define WIN_NAME "fract'ol"
/*
** full-screen window @42 -> 2560x1440
*/
# define X_SIZE 1920
# define Y_SIZE 1080

# define MANDELBROTX1 -2.1
# define MANDELBROTX2 0.6
# define MANDELBROTY1 -1.2
# define MANDELBROTY2 1.2

# define X_SCALING(x2, x1) ((float)X_SIZE / (x2 - x1))
# define Y_SCALING(y2, y1) ((float)Y_SIZE / (y2 - y1))

# define MAX_ITER 1000
/*
** definition of the t_ocl struct, which contain data for openCL functions.
*/
typedef struct			s_openCL_data
{
	cl_platform_id		*platforms;
	cl_device_id		device;
	cl_context			context;
	cl_program			program;
	cl_kernel			*kernels;
	cl_uint				kernels_nb;
	cl_command_queue	queue;
	void				*info;
	size_t				info_size;
}						t_ocl;

/*
** definition of the t_img struct, which contain an mlx-image's data.
*/
typedef struct			s_image_data
{
	void				*ptr;
	int					bpp;
	int					linesize;
	int					endian;
	int					*data;
/*
	int				x;
	int				y;
	int				color;
*/
}						t_img;

/*
** definition of the t_mlx struct, which contain data for mlx functions.
*/
typedef struct			s_mlx_data
{
	void				*mlxptr;
	void				*win;
	t_img				*img;
	void				*clrpick;
}						t_mlx;

/*
** definition of the t_fractol struct, which contain
** all data required for the program.
*/

typedef enum			e_fractal_name
{
	none,
	mandelbrot,
	julia,
}						t_name;

typedef struct			s_devices_status
{
	int					button;
	int					x;
	int					y;
	int					keycode;
}						t_status;

typedef struct			s_fractal
{
	t_name				name;
	float				x1;
	float				x2;
	float				y1;
	float				y2;
	float				z[2];
	float				c[2];
	cl_mem				iter_array;
	int					max_iter;
}						t_fractal;

typedef struct			s_fractol_data
{
	t_mlx				*mlx;
	t_ocl				*ocl;
	t_fractal			fract;
	t_status			status;
	void				**ptr;
}						t_fractol;

typedef void			(*t_funptr)(t_fractal *);
typedef struct			s_fractales_list
{
	t_name				name;
	t_funptr			f;
}						t_frct_lst;

/*
** declaration of the OpenCL-using functions :
*/
t_ocl					*ocl_init_context(int devices_number);
void					ocl_building_program(t_ocl *ocl, const char *src,
										const char *flags);
//ocl_building_program : il faut prendre le binaire, pas le source

/*
** declaration of the main functions :
*/
void					ft_error(const char *perror_msg, const char *message);
void					ft_usage(void);
//
t_mlx					*ft_init_mlx(void **anti_leaks_ptr);
t_ocl					*ft_init_opencl(void);
int						ft_create_kernels(t_ocl *ocl, const char *path);
void					ft_deallocate(t_fractol *frctl, void **anti_leaks_ptr);
void					ft_deallocate_mlx(t_mlx **mlx, void **anti_leaks_ptr);
void					*ft_deallocate_opencl(t_ocl **ocl,
												const char *debug_msg);
//
int						init_iter_array(t_fractol *frctl);
void					init_fract(t_fractol *frctl, const char *name);
void					init_mandelbrot(t_fractal *fract);
void					init_julia(t_fractal *fract);
void					ocl_mandelbrot(t_fractol *frctl, size_t *work_size);
void					ocl_read_kernel_result(t_fractol *frctl);
//
int						ft_mouse_event(int button, int x, int y, void *param);
int						key_hook(int keycode, void *param);
int						mouse_hook(int button, int x, int y, void *param);
void					ft_zoom(t_fractol *frctl, int where);
void					ft_reset(t_fractol *frctl);
int						ft_get_cursor_pos(int x, int y, void *param);
#endif
