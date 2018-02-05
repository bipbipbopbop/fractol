/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 13:40:37 by jhache            #+#    #+#             */
/*   Updated: 2018/01/11 12:17:34 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 32
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct	s_file_state
{
	int					fd;
	char				*line;
	struct s_file_state	*next;
}				t_gnl;

int				get_next_line(const int fd, char **line);

#endif
