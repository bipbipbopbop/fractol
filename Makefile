#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhache <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/15 17:18:48 by jhache            #+#    #+#              #
#    Updated: 2018/04/04 16:07:58 by jhache           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fractol

########################### COMPILATION ##########################

OPENCLC = /System/Library/Frameworks/OpenCL.framework/Libraries/openclc
CC = gcc

OPENCLCFLAGS = -Werror -cl-std=CL1.2 -emit-llvm -arch gpu_64 -I $(INCLUDESDIR)
CCFLAGS = -Wall -Werror -Wextra
CCFRAMEWORKS = -g -framework OpenGL -framework AppKit -framework opencl
CCLIBS = -L $(MLXDIR) -lmlx -L $(LIBFTDIR) -lft
CCINCLUDES = -I $(INCLUDESDIR) -I $(LIBFTINCLUDESDIR) -I $(MLXDIR)

############################# FILES ##############################

SRCS = main.c mlx_data.c opencl_data.c mandelbrot.c event.c mouse_event.c \
		init_fract.c tools.c zoom.c keyboard_event.c color.c \
		julia.c burning_ship.c
KERNELSRCS = mandelbrot.cl julia.cl burning_ship.cl

INCLUDES = fractol.h ft_clrpick.h ft_colorpicker.h mlx_keycode.h
KERNELSINCLUDES = kernels.h
LIBFTINCLUDES = ft_printf.h file_handling.h libft.h
MLXINCLUDES = mlx.h

### COLOR_PICKER FILES
SRCS += ft_bar.c ft_clrpick_event.c ft_colorpicker.c \
		ft_cursor.c ft_imgtools.c ft_sqr.c
INCLUDES += ft_clrpick.h ft_colorpicker.h
###

OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

#KERNELSBIN = $(addprefix $(KERNELSDIR)/, kernels.clbin)
KERNELSBIN = $(addprefix $(OBJSDIR)/, $(KERNELSRCS:.cl=.clbin))

MLX = libmlx.a
LIBFT = libft.a

########################### DIRECTORY ############################

SRCSDIR = srcs
COLOR_PICKER_DIR = srcs/color_picker
OBJSDIR = objs
KERNELSDIR = kernels
INCLUDESDIR = includes
LIBFTINCLUDESDIR = libft/includes
MLXDIR = minilibx
LIBFTDIR = libft

######################### RULES OPTIONS ##########################

vpath %.c $(SRCSDIR)
vpath %.c $(COLOR_PICKER_DIR)
vpath %.cl $(KERNELSDIR)
vpath %.h $(INCLUDESDIR)
vpath $(MLX) $(MLXDIR)
vpath $(LIBFT) $(LIBFTDIR)
.PHONY: all clean fclean re

############################# RULES ##############################x

all: $(MLX) $(LIBFT) $(NAME) $(KERNELSBIN)

$(NAME): $(OBJSDIR) $(INCLUDES) $(OBJS)
	$(CC) $(CCFRAMEWORKS) $(CCLIBS) -o $(NAME) $(OBJS)

$(OBJSDIR):
	mkdir -p $@

$(MLX):
	make -C $(MLXDIR)

$(LIBFT):
	make -C $(LIBFTDIR)

$(OBJSDIR)/%.o: %.c $(INCLUDES)
#	$(CC) -c $(CCFLAGS) $(CCINCLUDES) $< -o $@!!!!!
	$(CC) -c $(CCINCLUDES) $< -o $@

$(OBJSDIR)/%.clbin: %.cl $(KERNELSRCS) $(KERNELSINCLUDES)
	$(OPENCLC) $(OPENCLCFLAGS) -c $< -o $@

clean:
	/bin/rm -Rf $(OBJSDIR)
#	/bin/rm -f $(MLXDIR)/*.o	<- ici se trouve la trace de ma volonte d'avoir une feature rigoureuse, en depit de la norme 42
	make clean -C $(LIBFTDIR)

fclean: clean
	/bin/rm -f $(NAME)
	make clean -C $(MLXDIR)
	make fclean -C $(LIBFTDIR)

re: fclean all
