/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:57:53 by jhache            #+#    #+#             */
/*   Updated: 2018/01/08 13:40:55 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define INITIALIZE	-2
#define ERROR		-1

/*
** count_return: this function counts the number of printed characters
** and returns it for the return value of ft_printf.
*/

int			ft_count_return(int i)
{
	static int	count = 0;

	if (i == ERROR)
		count = ERROR;
	else if (i == INITIALIZE && count != ERROR)
		count = 0;
	else if (count > ERROR)
		count += i;
	return (count);
}

/*
** makestr: takes the "format" string from ft_printf and creates
** fragments of strings with computed conversions,
** which are printed one by one.
*/

static int	ft_makestr_process(const char *str, char **s, va_list ap, int i)
{
	char	*tmp;
	int		j;

	if (str[i] == '%')
	{
		*s = ft_convstr((str + i + 1), ap, s);
		j = (ft_mulcharpos((str + i + 1), "pdDioOuUxXbcCsSB%") + 2);
		if (*s != NULL)
		{
			ft_count_return(write(1, *s, ft_strlen(*s)));
			ft_strdel(s);
			*s = ft_strnew(0);
		}
	}
	else
	{
		j = ((ft_strchr(str + i, '%') == NULL) ? ft_strlen(str + i)
			: ft_charpos(str + i, '%'));
		tmp = ft_strsub(str, i, j);
		*s = ft_strjoinfree(*s, tmp, BOTH);
	}
	if (*s == NULL)
		return (ERROR);
	return (j);
}

static void	ft_makestr(const char *str, va_list ap)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	s = ft_strnew(0);
	while (str[i])
	{
		j = ft_makestr_process(str, &s, ap, i);
		if (j == ERROR)
			return ;
		i += j;
	}
	if (s[0] != 0)
		ft_count_return(write(1, s, ft_strlen(s)));
	ft_strdel(&s);
}

/*
** ft_printf: it's the first called function, which will transform
** the "format" string into a string with computed conversions,
** and which will print that new string on stdout (1).
*/

int			ft_printf(const char *format, ...)
{
	va_list	ap;

	ft_count_return(INITIALIZE);
	if (ft_strchr(format, '%') == NULL)
		return (ft_count_return(write(1, format, ft_strlen(format))));
	va_start(ap, format);
	ft_makestr(format, ap);
	va_end(ap);
	return (ft_count_return(0));
}
