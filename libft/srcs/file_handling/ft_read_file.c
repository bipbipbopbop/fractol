/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 11:59:42 by jhache            #+#    #+#             */
/*   Updated: 2018/02/25 12:51:51 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_handling.h"

char	*ft_read_file(const char *file_name, size_t *size)
{
	int		fd;
	int		ret;
	char	*result;
	char	buff[BUFF_SIZE + 1];

	ft_bzero(buff, BUFF_SIZE);
	fd = open(file_name, O_RDONLY);
	if (size != NULL)
		*size = 0;
	if (fd <= 0)
		return (NULL);
	result = ft_strnew(0);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		result = ft_strjoinfree(result, buff, FIRST);
		if (size != NULL)
			*size += ret;
	}
	close(fd);
	if (ret < 0)
		return (NULL);
	return (result);
}
