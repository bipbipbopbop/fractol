#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhache <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/28 17:10:59 by jhache            #+#    #+#              #
#    Updated: 2018/02/28 17:46:44 by jhache           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fractol

OPENCLC = openclc
CC = gcc

OPENCLCFLAGS = -cl-std=CL1.2 -emit-llvm -arch gpu_64
CCFLAGS = -Wall -Werror -Wextra
CCFRAMEWORKS = -framework OpenGL -framework AppKit
CCLIBS = -L $(MLXDIR) -lmlx -L $(LIBFTDIR) -lft
CCINCLUDES = -I $(INCLUDESDIR) -I $(LIBFTINCLUDESDIR)

###########################################################
SRCS = FILES.c
SRCS += COLOR_PICKER.c
OBJS = $(SRCS:.c=.o)
INCLUDES = FILES.h
LIBFT = libft.a
MLX = mlx.a
###########################################################

LIBFTINCLUDES = ft_printf.h file_handling.h libft.h
MLXINCLUDES = mlx.h

SRCSDIR = srcs
COLOR_PICKERDIR = srcs/color_picker
OBJSDIR = objs
INCLUDESDIR = includes
LIBFTINCLUDESDIR = libft/includes
MLXDIR = minilibx
LIBFTDIR = libft


vpath %.c $(SRCSDIR)
vpath %.c $(COLOR_PICKER_DIR)
vpath %.h $(INCLUDESDIR)
vpath $(MLX) $(MLXDIR)
vpath $(LIBFT) $(LIBFTDIR)
.PHONY: all clean fclean re


all: $(NAME)

$(NAME): $(OBJSDIR) $(MLX) $(LIBFT) $(addprefix $(OBJSDIR)/, $(OBJS)) $(INCLUDES)
	$(CC) $(CCLIBS) $(CCFRAMEWORKS) -o $(NAME) $(addprefix $(OBJSDIR)/, $(OBJS))

$(OBJSDIR):
	mkdir -p $@

$(MLX):
	make -C $(MLXDIR)

$(LIBFT):
	make -C $(LIBFTDIR)

(addprefic $(OBJSDIR/, %.o): %.c
	$(CC) -c $(CCFLAGS) $(CCINCLUDES) $< -o $@

clean:
	/bin/rm -Rf $(OBJSDIR)
#	/bin/rm -f $(MLXDIR)/*.o	<- ici est garder comme trace la volonte d'avoir une feature rigoureuse, en depit de la norme 42
	make clean -C $(LIBFTDIR)

fclean: clean
	/bin/rm -f $(NAME)
	make clean -C $(MLXDIR)
	make fclean -C $(LIBFTDIR)

re: fclean all
