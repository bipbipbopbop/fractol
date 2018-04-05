/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversionbf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 15:06:11 by jhache            #+#    #+#             */
/*   Updated: 2018/01/10 16:45:00 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define TAB_SIZE 2048

/*
** Brainfuck : this function is an interpreter for Brainfuck code.
** it receives a const char *code, which contains the brainfuck code,
** a char *workplace, which is a string with all case == 0.
** all operations are done in the workplace string,
** and a char *result, which will hold the result of the interpreter.
*/

static void	ft_loop_start(char workplace, const char **code, int *original)
{
	int	loop;

	loop = ++(*original);
	if (workplace != 0)
		return ;
	while (**code != ']' || loop != (*original - 1))
	{
		++(*code);
		if (**code == '[')
			++loop;
		else if (**code == ']')
			--loop;
	}
}

static void	ft_loop_end(char workplace, const char **code, int *original)
{
	int	loop;

	loop = *original;
	if (workplace == 0)
		return ;
	while (**code != '[' || loop != (*original - 1))
	{
		--(*code);
		if (**code == '[')
			--loop;
		else if (**code == ']')
			++loop;
	}
	ft_loop_start(workplace, code, original);
}

static void	ft_interpreter(char *workplace, const char *code, char *result)
{
	int	loop;

	loop = 0;
	while (*code != '\0')
	{
		if (*code == '+')
			++(*workplace);
		else if (*code == '-')
			--(*workplace);
		else if (*code == '>')
			++workplace;
		else if (*code == '<')
			--workplace;
		else if (*code == '.')
		{
			*result = *workplace;
			++result;
		}
		else if (*code == '[')
			ft_loop_start(*workplace, &code, &loop);
		else if (*code == ']')
			ft_loop_end(*workplace, &code, &loop);
		++code;
	}
}

/*
** the ft_brainfuck function is a check of the code string.
** if an error is found, the interpreter function is not called.
*/

static void	ft_convbf(char *workplace, const char *code, char *result)
{
	int		braces_count;
	int		i;

	i = 0;
	braces_count = 0;
	while (code[i])
	{
		if (code[i] == '[')
			++braces_count;
		if (code[i] == ']')
			--braces_count;
		++i;
	}
	if (braces_count == 0)
	{
		ft_interpreter(workplace, code, result);
	}
}

char		*ft_convbrainfuck(t_opt *opt, va_list ap)
{
	char	*result;
	char	*code;
	char	*tmp;
	char	tab[TAB_SIZE];

	if (opt->conversion != 'B')
		return (NULL);
	ft_bzero(tab, TAB_SIZE);
	result = ft_strnew(TAB_SIZE);
	code = va_arg(ap, char *);
	if (code == NULL)
		return (NULL);
	ft_convbf(tab, code, result);
	if (opt->precision != UNDEFINED && (int)ft_strlen(result) > opt->precision)
	{
		tmp = ft_strsub(result, 0, opt->precision);
		ft_strdel(&result);
		if (tmp != NULL)
			result = tmp;
	}
	return (result);
}
