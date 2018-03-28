#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhache <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/15 17:18:48 by jhache            #+#    #+#              #
#    Updated: 2018/03/28 13:13:28 by jhache           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fractol

########################### COMPILATION ##########################

OPENCLC = /System/Library/Frameworks/OpenCL.framework/Libraries/openclc
CC = gcc

OPENCLCFLAGS = -cl-std=CL1.2 -emit-llvm -arch gpu_64
CCFLAGS = -Wall -Werror -Wextra
CCFRAMEWORKS = -g -framework OpenGL -framework AppKit -framework opencl
CCLIBS = -L $(MLXDIR) -lmlx -L $(LIBFTDIR) -lft
CCINCLUDES = -I $(INCLUDESDIR) -I $(LIBFTINCLUDESDIR)

############################# FILES ##############################

SRCS = main.c mlx_data.c opencl_data.c mandelbrot.c event.c mouse_event.c \
		init_fract.c tools.c zoom.c keyboard_event.c

INCLUDES = fractol.h ft_clrpick.h ft_colorpicker.h mlx_keycode.h
LIBFTINCLUDES = ft_printf.h file_handling.h libft.h
MLXINCLUDES = mlx.h

### COLOR_PICKER FILES
SRCS += ft_bar.c ft_clrpick_event.c ft_colorpicker.c \
		ft_cursor.c ft_imgtools.c ft_sqr.c
INCLUDES += ft_clrpick.h ft_colorpicker.h
###

OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

KERNELSRCS = $(addprefix $(KERNELSDIR)/, mandelbrot.cl)
KERNELBIN = $(addprefix $(KERNELSDIR)/, mandelbrot.clbin)
#OBJECTIF: compiler les kernels separemment, comme pour les .o

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
vpath %.h $(INCLUDESDIR)
vpath $(MLX) $(MLXDIR)
vpath $(LIBFT) $(LIBFTDIR)
.PHONY: all clean fclean re

############################# RULES ##############################x

all: $(MLX) $(LIBFT) $(NAME) $(KERNELBIN)

$(NAME): $(OBJSDIR) $(INCLUDES) $(OBJS)
	$(CC) $(CCFRAMEWORKS) $(CCLIBS) -o $(NAME) $(OBJS)

$(OBJSDIR):
	mkdir -p $@

$(MLX):
	make -C $(MLXDIR)

$(LIBFT):
	make -C $(LIBFTDIR)

$(OBJSDIR)/%.o: %.c $(INCLUDES)
	$(CC) -c $(CCINCLUDES) $< -o $@
#	$(CC) -c $(CCFLAGS) $(CCINCLUDES) $< -o $@ //les flags de compilation ont ete retire temporairement

$(KERNELBIN): $(KERNELSRCS)
#	$(OPENCLC) $(OPENCLCFLAGS) -I $(INCLUDESDIR) -c $< -o $@
	$(OPENCLC) $(OPENCLCFLAGS) -c $< -o $@
clean:
	/bin/rm -Rf $(OBJSDIR)
	/bin/rm -f $(KERNELBIN)
#	/bin/rm -f $(MLXDIR)/*.o	<- ici se trouve la trace de ma volonte d'avoir une feature rigoureuse, en depit de la norme 42
	make clean -C $(LIBFTDIR)

fclean: clean
	/bin/rm -f $(NAME)
	make clean -C $(MLXDIR)
	make fclean -C $(LIBFTDIR)

re: fclean all
