/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 16:09:38 by jhache            #+#    #+#             */
/*   Updated: 2018/01/08 15:09:54 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** definition of the global t_conv array,
** which associate each conversion function to the corresponding char.
*/
static t_conv	g_conv[] = {
	{'s', &ft_convs},
	{'S', &ft_convls},
	{'p', &ft_convp},
	{'i', &ft_convd},
	{'d', &ft_convd},
	{'D', &ft_convd},
	{'u', &ft_convu},
	{'U', &ft_convu},
	{'b', &ft_convb},
	{'o', &ft_convo},
	{'O', &ft_convo},
	{'x', &ft_convx},
	{'X', &ft_convx},
	{'c', &ft_convc},
	{'C', &ft_convc},
	{'B', &ft_convbrainfuck},
	{'%', &ft_convpercent}};
/*
** field_width : this function applies the field width
** to the computed conversion string. this function is called
** when no option functions are needed.
*/

static char	*ft_field_width(t_opt *opt, char *s)
{
	int		i;
	char	*padding;

	if (s == NULL)
		return (NULL);
	i = opt->field - ft_strlen(s);
	if (i > 0)
	{
		padding = ft_strnew(i);
		ft_memset(padding, ' ', i);
		s = (ft_strchr(opt->attribute, '-') != NULL && opt->conversion != 'n') ?
			ft_strjoinfree(s, padding, BOTH) : ft_strjoinfree(padding, s, BOTH);
	}
	return (s);
}

static char	*ft_joinstring(t_opt *opt, char *conv, char **befo_conv)
{
	char	*tmp;

	if (conv == NULL || *befo_conv == NULL)
	{
		ft_strdel(befo_conv);
		ft_strdel(&conv);
		return (NULL);
	}
	ft_count_return(write(1, *befo_conv, ft_strlen(*befo_conv)));
	if (ft_strchr("cC", opt->conversion) != NULL && conv[0] == 0)
	{
		--opt->field;
		tmp = ft_strnew(0);
		tmp = ft_field_width(opt, tmp);
		ft_count_return(((ft_strchr(opt->attribute, '-') != NULL) ?
						write(1, conv, 1) : write(1, tmp, ft_strlen(tmp))));
		ft_count_return(((ft_strchr(opt->attribute, '-') == NULL) ?
						write(1, conv, 1) : write(1, tmp, ft_strlen(tmp))));
		ft_strdel(&tmp);
	}
	ft_strdel(befo_conv);
	return (conv);
}

/*
** convstr: take all the options in the t_opt var
** and send it to the functions who will compute the results.
*/

char		*ft_convstr(const char *str, va_list ap, char **s)
{
	char	*result;
	t_opt	*opt;
	int		i;

	i = 0;
	if ((opt = ft_setopt(str, ap)) == NULL)
	{
		ft_strdel(s);
		return (NULL);
	}
	while (opt->conversion != g_conv[i].c)
		++i;
	result = g_conv[i].f(opt, ap);
	if (ft_strchr("dDioOuUxXb%", opt->conversion) != NULL)
		result = ft_optionint(opt, result);
	else if (ft_strchr("cC", opt->conversion) == NULL
			|| (result != NULL && result[0] != 0))
		result = ft_field_width(opt, result);
	result = ft_replacesign(result, opt);
	result = ft_joinstring(opt, result, s);
	ft_strdel(&(opt->attribute));
	ft_strdel(&(opt->len_modif));
	ft_memdel((void **)&opt);
	return (result);
}
