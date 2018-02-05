/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:59:30 by jhache            #+#    #+#             */
/*   Updated: 2018/01/10 16:43:29 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** includes of the needed librairies
*/
# include <stdarg.h>
# include <wchar.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdint.h>
# include "libft.h"

/*
** definition of the t_opt struct,
** which will stores all the informations
** about the conversion string.
*/
typedef struct	s_options
{
	char	conversion;
	char	*attribute;
	int		field;
	int		precision;
	char	*len_modif;
}				t_opt;

/*
** definition of macros for better comprehension
** of precision and field width values.
*/
# define ARG_NEEDED -2
# define UNDEFINED	-1
# define PREC_NULL	0

/*
** definition of the t_conv struct,
** which will stores the function address coresponding
** to the conversion specifier in the conversion string.
*/
typedef char	*(*t_funptr)(t_opt *, va_list);
typedef struct	s_conversion_specification
{
	char			c;
	t_funptr		f;
}				t_conv;

/*
** Prototypes of the main functions
*/
int				ft_printf(const char *format, ...);
int				ft_count_return(int i);
char			*ft_convstr(const char *str, va_list ap, char **s);
t_opt			*ft_setopt(const char *str, va_list ap);
char			*ft_optionint(t_opt *opt, char *s);
char			*ft_replacesign(char *s, t_opt *opt);
/*
** Prototypes of the conversion functions
*/
char			*ft_convs(t_opt *opt, va_list ap);
char			*ft_convls(t_opt *opt, va_list ap);
char			*ft_convc(t_opt *opt, va_list ap);
char			*ft_convlc(wint_t c);
char			*ft_convd(t_opt *opt, va_list ap);
char			*ft_convu(t_opt *opt, va_list ap);
char			*ft_convb(t_opt *opt, va_list ap);
char			*ft_convo(t_opt *opt, va_list ap);
char			*ft_convx(t_opt *opt, va_list ap);
char			*ft_convp(t_opt *opt, va_list ap);
char			*ft_convbrainfuck(t_opt *opt, va_list ap);
char			*ft_convpercent(t_opt *opt, va_list ap);
#endif
