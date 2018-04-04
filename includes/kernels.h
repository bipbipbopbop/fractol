/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernels.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 18:46:57 by jhache            #+#    #+#             */
/*   Updated: 2018/04/04 21:37:42 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KERNELS_H
# define KERNELS_H

# ifndef LIBFT_H
#  define ABS(x) ((x < 0) ? -(x) : x)
# endif

/*
** # if defined(cl_khr_fp64)
** #  define DOUBLE_SUPPORT_AVAILABLE
** #  elif defined(cl_amd_fp64)
** #  define DOUBLE_SUPPORT_AVAILABLE
** # endif
**
** # ifdef DOUBLE_SUPPORT_AVAILABLE
** typedef double t_real;
** #  else
** typedef float t_real;
** # endif
*/
typedef float	t_real;
#endif
