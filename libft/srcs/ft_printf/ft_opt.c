/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 12:43:24 by jhache            #+#    #+#             */
/*   Updated: 2018/01/08 16:07:18 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_setattribute(char **s, t_opt **opt)
{
	int		pos;
	char	*tab;
	char	*tmp;

	tab = ft_strdup("123456789*.hljz?\0");
	tab[15] = (*opt)->conversion;
	pos = ft_mulcharpos(*s, tab);
	if (pos == 0)
	{
		(*opt)->attribute = ft_strnew(0);
		ft_strdel(&tab);
		return ;
	}
	(*opt)->attribute = ft_strsub(*s, 0, pos);
	tmp = ft_strsub(*s, pos, (ft_strlen(*s) - pos));
	ft_strdel(s);
	*s = tmp;
	if (*s == NULL || (*opt)->attribute == NULL)
		ft_memdel((void **)opt);
	tmp = (*opt)->attribute;
	ft_strdel(&tab);
}

static void	ft_setfield(char **s, t_opt **opt)
{
	int		pos;
	char	*tab;
	char	*tmp;

	if (*opt == NULL)
		return ;
	tab = ft_strdup(".hljz?\0");
	tab[5] = (*opt)->conversion;
	pos = ft_mulcharpos(*s, tab);
	if (pos == 0)
	{
		(*opt)->field = UNDEFINED;
		ft_strdel(&tab);
		return ;
	}
	(*opt)->field = ((pos == 1 && (*s)[0] == '*')
					? ARG_NEEDED : ft_atoi(*s));
	tmp = ft_strsub(*s, pos, (ft_strlen(*s) - pos));
	ft_strdel(s);
	*s = tmp;
	if (*s == NULL)
		ft_memdel((void **)opt);
	ft_strdel(&tab);
}

static void	ft_setprecision(char **s, t_opt **opt, va_list ap)
{
	int		pos;
	char	*tab;
	char	*tmp;

	if (*opt == NULL)
		return ;
	tab = ft_strdup("hljz?\0");
	tab[4] = (*opt)->conversion;
	pos = ft_mulcharpos(*s, tab);
	if (pos == 0 || pos == 1)
		(*opt)->precision = ((pos == 0) ? UNDEFINED : PREC_NULL);
	else if (pos == 2 && (*s)[1] == '*')
	{
		(*opt)->precision = va_arg(ap, int);
		(*opt)->precision *= (((*opt)->precision < 0) ? PREC_NULL : 1);
	}
	else
		(*opt)->precision = ft_atoi(*(s) + 1);
	tmp = *s;
	*s = ft_strsub(tmp, pos, (ft_strlen(tmp) - pos));
	ft_strdel(&tmp);
	if (*s == NULL)
		ft_memdel((void **)opt);
	ft_strdel(&tab);
}

static void	ft_setlen(char **s, t_opt **opt)
{
	int		pos;

	if (*opt == NULL)
		return ;
	pos = ft_charpos(*s, (*opt)->conversion);
	if (pos == 0)
	{
		(*opt)->len_modif = NULL;
		ft_strdel(s);
		return ;
	}
	(*opt)->len_modif = ft_strsub(*s, 0, pos);
	ft_strdel(s);
	if ((*opt)->len_modif == NULL || pos > 2)
		ft_memdel((void **)opt);
}

/*
** setopt : this function will create the t_opt var
** for the corresponding conversion string.
*/

t_opt		*ft_setopt(const char *str, va_list ap)
{
	t_opt	*opt;
	char	*tmp;

	if ((tmp = ft_strstr(str, "pdDioOuUxXbcCsSB%", CHAR)) == NULL)
		return (NULL);
	if ((opt = (t_opt *)malloc(sizeof(t_opt))) == NULL)
		return (NULL);
	opt->conversion = *tmp;
	tmp = ft_strsub(str, 0, (size_t)((tmp - str) + 1));
	ft_setattribute(&tmp, &opt);
	ft_setfield(&tmp, &opt);
	ft_setprecision(&tmp, &opt, ap);
	ft_setlen(&tmp, &opt);
	if (opt != NULL && opt->field == ARG_NEEDED)
	{
		opt->field = va_arg(ap, int);
		if (opt->field < 0)
			opt->attribute = ft_strjoinfree(opt->attribute, "-", FIRST);
		if (opt->field == 0)
			opt->attribute = ft_strjoinfree(opt->attribute, "0", FIRST);
		opt->field *= ((opt->field < 0) ? -1 : 1);
	}
	return (opt);
}
