/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 17:54:21 by rsibiet           #+#    #+#             */
/*   Updated: 2016/02/15 19:58:30 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_read_line(int const fd, char *sav_fd[fd])
{
	char		*pos;
	char		*temp;
	int			i;
	char		buff[BUFF_SIZE + 1];

	i = 0;
	while ((!(pos = ft_strchr(sav_fd[fd], '\n'))) &&
			((i = read(fd, buff, BUFF_SIZE)) > 0))
	{
		buff[i] = '\0';
		temp = sav_fd[fd];
		sav_fd[fd] = ft_strjoin(temp, buff);
		ft_strdel(&temp);
	}
	if (i == -1)
		return (-1);
	if (i == 0 && pos == NULL)
		return (0);
	return (1);
}

int			get_next_line(int const fd, char **line)
{
	static char		*sav_fd[256] = {NULL};
	int				i;

	if (line == NULL || fd < 0 || fd > 255)
		return (-1);
	if (sav_fd[fd] == NULL)
		sav_fd[fd] = ft_strdup("");
	if ((i = ft_read_line(fd, sav_fd)) == 0)
	{
		*line = sav_fd[fd];
		if (ft_strlen(sav_fd[fd]) == 0)
			return (0);
		sav_fd[fd] = NULL;
		return (1);
	}
	else if (i == -1)
		return (-1);
	*line = ft_strsub(sav_fd[fd], 0, (ft_strchr(sav_fd[fd], '\n'))
			- sav_fd[fd]);
	sav_fd[fd] = ft_strdup(ft_strchr(sav_fd[fd], '\n') + 1);
	return (1);
}
