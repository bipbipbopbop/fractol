/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 12:51:07 by jhache            #+#    #+#             */
/*   Updated: 2018/02/25 13:28:43 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HANDLING_H
# define FILE_HANDLING_H

# define BUFF_SIZE 32
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct	s_gnl
{
	int				fd;
	char			*line;
	struct s_gnl	*next;
}				t_gnl;

int				get_next_line(const int fd, char **line);
char			*ft_read_file(const char *file_name, size_t *size);

#endif
