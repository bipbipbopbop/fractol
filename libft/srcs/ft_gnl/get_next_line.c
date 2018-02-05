/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 13:38:23 by jhache            #+#    #+#             */
/*   Updated: 2017/11/30 16:48:13 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_fd(const int fd, t_gnl **lst)
{
	t_gnl	*new;
	t_gnl	*tmp;

	tmp = *lst;
	while (tmp != NULL)
	{
		if (tmp->fd == fd)
			return (0);
		tmp = tmp->next;
	}
	new = (t_gnl *)malloc(sizeof(t_gnl));
	if (new == NULL)
		return (-1);
	new->fd = fd;
	new->line = ft_strnew(0);
	if (new->line == NULL)
		return (-1);
	new->next = *lst;
	*lst = new;
	return (0);
}

static int	eoleofcheck(char **line, t_gnl *ls)
{
	if (*(ls->line) == '\0')
		return (0);
	else
	{
		if ((*line = ft_strdup(ls->line)) == NULL)
			return (-1);
		ft_strdel(&(ls->line));
		return (1);
	}
}

static int	find_next_line(const int fd, char **line, t_gnl *ls, char *buffer)
{
	char			*tmp;
	unsigned int	el;
	int				ret;

	if ((tmp = ft_strchr(ls->line, '\n')) != NULL)
	{
		el = (unsigned int)(tmp - ls->line);
		if ((*line = ft_strsub(ls->line, 0, (size_t)el++)) == NULL)
			return (-1);
		if ((tmp = ft_strsub(ls->line, el, (ft_strlen(ls->line) - el))) == NULL)
			return (-1);
		ft_strdel(&(ls->line));
		ls->line = tmp;
		return (1);
	}
	ft_bzero(buffer, (BUFF_SIZE + 1));
	if ((ret = read(fd, buffer, BUFF_SIZE)) == 0)
		return (eoleofcheck(line, ls));
	if (ret == -1)
		return (-1);
	ls->line = ft_strjoinfree(ls->line, buffer, FIRST);
	return (find_next_line(fd, line, ls, buffer));
}

int			get_next_line(const int fd, char **line)
{
	static t_gnl	*begin_list;
	t_gnl			*tmp;
	char			buffer[BUFF_SIZE + 1];

	if (line == NULL || fd < 0)
		return (-1);
	if (check_fd(fd, &begin_list) == -1)
		return (-1);
	tmp = begin_list;
	while (tmp->fd != fd)
		tmp = tmp->next;
	if (tmp->line == NULL)
		return (0);
	return (find_next_line(fd, line, tmp, buffer));
}
