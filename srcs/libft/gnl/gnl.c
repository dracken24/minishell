/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:14:14 by nadesjar          #+#    #+#             */
/*   Updated: 2022/07/31 22:26:07 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"
#include <limits.h>

char	*ft_read_fd(int fd, char *save_str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchrr(save_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		save_str = ft_strjoinn(save_str, buff);
	}
	free(buff);
	return (save_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save_str[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	save_str[fd] = ft_read_fd(fd, save_str[fd]);
	if (!save_str[fd])
		return (NULL);
	line = ft_get_line(save_str[fd]);
	save_str[fd] = ft_get_nline(save_str[fd]);
	return (line);
}
