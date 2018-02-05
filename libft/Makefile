# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhache <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 13:40:24 by jhache            #+#    #+#              #
#    Updated: 2018/01/11 12:22:45 by jhache           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra

AR = ar
ARFLAGS = rc

SRCSDIR = srcs/
INCLUDESDIR = includes/
OBJSDIR = objs/

#LIBFT .c files
SRCS = ft_atoi.c ft_llitoa.c ft_memcpy.c ft_putstr.c ft_strjoin.c ft_strrev.c \
ft_bzero.c ft_llitoa_base.c ft_memdel.c ft_putstr_fd.c ft_strjoinfree.c ft_strrstr.c \
ft_charpos.c ft_lstadd.c ft_memmove.c ft_sqrt.c ft_strlcat.c ft_strsplit.c \
ft_convert_base.c ft_lstdel.c ft_memset.c ft_strcat.c ft_strlen.c ft_strstr.c \
ft_imaxtoa.c ft_lstdelone.c ft_mulcharpos.c ft_strchr.c ft_strmap.c ft_strsub.c \
ft_imaxtoa_base.c ft_lstiter.c ft_nbrlen.c ft_strclr.c ft_strmapi.c ft_strtrim.c \
ft_isalnum.c ft_lstlen.c ft_power.c ft_strcmp.c ft_strncat.c ft_tolower.c \
ft_isalpha.c ft_lstmap.c ft_putchar.c ft_strcpy.c ft_strncmp.c ft_toupper.c \
ft_isascii.c ft_lstnew.c ft_putchar_fd.c ft_strdel.c ft_strncpy.c ft_uimaxtoa.c \
ft_isdigit.c ft_memalloc.c ft_putendl.c ft_strdup.c ft_strnequ.c ft_uimaxtoa_base.c \
ft_isprint.c ft_memccpy.c ft_putendl_fd.c ft_strequ.c ft_strnew.c ft_ullitoa.c \
ft_itoa.c ft_memchr.c ft_putnbr.c ft_striter.c ft_strnstr.c ft_ullitoa_base.c \
ft_itoa_base.c ft_memcmp.c ft_putnbr_fd.c ft_striteri.c ft_strrchr.c
#GET_NEXT_LINE .c files
SRCS += get_next_line.c
#FT_PRINTF .c files
SRCS += conversionbf.c conversioncs.c conversionint.c \
conversionmis.c ft_convstr.c ft_opt.c ft_optionint.c ft_printf.c
OBJS = $(SRCS:%.c=%.o)

vpath %.c srcs
vpath %.c srcs/ft_gnl
vpath %.c srcs/ft_printf


.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJSDIR) $(addprefix $(OBJSDIR), $(OBJS))
	@ar $(ARFLAGS) $(NAME) $(addprefix $(OBJSDIR), $(OBJS))
	@ranlib $(NAME)
	@echo "$(NAME) done."

$(OBJSDIR):
	@mkdir -p $@

$(addprefix $(OBJSDIR), %.o): %.c
	@$(CC) $(CFLAGS) -I $(INCLUDESDIR) -c $< -o $@

clean:
	@/bin/rm -Rf $(OBJSDIR)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all