/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 13:08:35 by jhache            #+#    #+#             */
/*   Updated: 2018/04/02 19:11:26 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif
# include "libft.h"
# include "file_handling.h"
# include "ft_colorpicker.h"
# include "mlx.h"
# include "mlx_keycode.h"
# include <stdio.h>
# include <errno.h>

/*
** kernels infos :
*/
# define KERNELS_NB 3
# define KERNEL_PATH "./kernels/kernels.clbin"
# define OPENCL_BUILD_FLAGS "-Werror"

/*
** kernels index :
*/
# define MDBRT 0
# define JULIA 1
# define BURNS 2

/*
** first definition set for fractals :
*/
# define MANDELBROTX1 -2.1
# define MANDELBROTX2 0.6
# define MANDELBROTY1 -1.2
# define MANDELBROTY2 1.2

# define JULIAX1 -1.25
# define JULIAX2 1.25
# define JULIAY1 -1.25
# define JULIAY2 1.25

# define BURNINGSX1 -2.5
# define BURNINGSX2 1
# define BURNINGSY1 -2
# define BURNINGSY2 1
/*
** Image computing info :
** (full-screen window @42 -> 2560x1440)
*/
# define WIN_NAME "fract'ol"

# define X_SIZE 1920
# define Y_SIZE 1080

# define X_SCALING(x2, x1) ((float)X_SIZE / (x2 - x1))
# define Y_SCALING(y2, y1) ((float)Y_SIZE / (y2 - y1))

# define MAX_ITER 100

/*
** definition of the t_ocl struct, which contain data for openCL functions.
*/
typedef struct			s_opencl_data
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
}						t_img;

/*
** definition of the t_mlx struct, which contain data for mlx functions.
*/
typedef struct			s_mlx_data
{
	void				*mlxptr;
	void				*win;
	t_img				*img;
}						t_mlx;

/*
** definition of the t_name enum, which is used to choose
** the appropriate functions according to the selected fractal.
*/
typedef enum			e_fractal_name
{
	none,
	mandelbrot,
	julia,
	burning_ship,
}						t_name;

/*
** definition of the t_clr_type enum, which is used to choose
** the appropriate colorization function.
*/
typedef enum			e_color_type
{
	gradient,
	reverse_gradient,
	modulo_steps,
	randomator2000,
}						t_clr_type;

/*
** definition of the t_status struct, which store informations
** for the event. the cursor_pos_param array hold the x and y pos
** of the cursor when the Julia's C parameters are locked
** (stop is the corresponding boolean).
*/
typedef struct			s_devices_status
{
	int					button;
	int					x;
	int					y;
	int					cursor_pos_param[2];
	int					stop;
}						t_status;

/*
** definition of the t_color union, which allow to access to the color
** of a pixel one bit at a time.
*/
typedef union			u_color
{
	int					color;
	unsigned char		byte[4];
}						t_color;

/*
** definition of the t_fractal struct, which old information about the current
** displayed fractal.
*/
typedef struct			s_fractal
{
	t_name				name;
	float				x1;
	float				x2;
	float				y1;
	float				y2;
	t_color				clr;
	t_clr_type			clr_type;
	cl_mem				iter_array;
	int					max_iter;
}						t_fractal;

/*
** definition of the t_fractol struct, which contain
** all data required for the program.
*/
typedef struct			s_fractol_data
{
	t_mlx				*mlx;
	t_ocl				*ocl;
	t_fractal			fract;
	t_status			status;
	void				*clrpick;
	void				**ptr;
}						t_fractol;

/*
** definition of the t_frct_lst struct, which is used to referenced every
** available fractals.
*/
typedef void			(*t_initptr)(t_fractal *);
typedef void			(*t_frctptr)(t_fractol *, size_t *);
typedef struct			s_fractales_list
{
	t_name				name;
	t_initptr			init_ptr;
	t_frctptr			fun_ptr;
}						t_frct_lst;

/*
** definition of the t_frct_clr_type struct, which is used to referenced every
** available colorization method.
*/
typedef void			(*t_clrptr)(t_fractol *, int *);
typedef struct			s_colorization_type
{
	t_clr_type			type;
	t_clrptr			fun_ptr;
}						t_frct_clr_type;

/*
** declaration of the global array g_fract and g_clr_type,
** which referenced the functions linked to the fractal / the color method.
*/
# ifdef FRACTOL_MAIN

t_frct_lst				g_fract[];
t_frct_clr_type			g_clr_type[];

# else

extern t_frct_lst		g_fract[];
extern t_frct_clr_type	g_clr_type[];

# endif

/*
** DECLARATION OF THE PROGRAM FUNCTIONS
** Error & Exit functions:
*/
void					ft_error(const char *perror_msg, const char *message);
void					ft_usage(void);
void					ft_deallocate(t_fractol *frctl, void **anti_leaks_ptr);
void					ft_deallocate_mlx(t_mlx **mlx, void **anti_leaks_ptr);
void					*ft_deallocate_opencl(t_ocl **ocl,
												const char *debug_msg);
/*
** Initialization functions :
*/
t_mlx					*ft_init_mlx(void **anti_leaks_ptr);
t_ocl					*ft_init_opencl(void);
int						init_iter_array(t_fractol *frctl);
int						ft_create_kernels(t_ocl *ocl, const char *path);
/*
** Main computing functions :
*/
t_name					ft_select_fract(const char *name);
void					init_fract(t_fractol *frctl, t_name name);
void					init_mandelbrot(t_fractal *fract);
void					init_julia(t_fractal *fract);
void					init_burning_ship(t_fractal *fract);
void					ocl_mandelbrot(t_fractol *frctl, size_t *work_size);
void					ocl_julia(t_fractol *frctl, size_t *work_size);
void					ocl_burning_ship(t_fractol *frctl, size_t *work_size);
/*
** Drawing functions :
*/
void					ocl_read_kernel_result(t_fractol *frctl);
void					colorize(t_fractol *frctl, int *fract_array);
int						get_color(int color, void *param);
void					ft_change_color_type(t_fractol *frctl, int mode);
void					color_reverse_gradient(t_fractol *frctl,
											int *fract_array);
void					color_gradient(t_fractol *frctl, int *fract_array);
void					color_steps(t_fractol *frctl, int *fract_array);
void					color_random(t_fractol *frctl, int *fract_array);
/*
** Event functions :
*/
void					init_hook(t_fractol *frctl);
int						key_hook(int keycode, void *param);
int						ft_mouse_event(int button, int x, int y, void *param);
void					ft_zoom(t_fractol *frctl, int where);
void					ft_move(t_fractol *frctl, int keycode);
void					ft_reset(t_fractol *frctl);
void					ft_change_max_iter(t_fractol *frctl, int sign);
int						ft_get_cursor_pos(int x, int y, void *param);
#endif
