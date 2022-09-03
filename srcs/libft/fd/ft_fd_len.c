/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:52:09 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/02 11:48:31 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/****** Open adnd read a fd or doc name for good len for malloc ******/

size_t	ft_read(char *buffer, int len, int fd_ext)
{
	len = read(fd_ext, buffer, BUFFER_SIZE);
	if (len < 0)
	{
		free(buffer);
		return (0);
	}
	return (len);
}

size_t	ft_fd_len_suite(char *name, char *buffer, int fd, int len)
{
	fd = open(name, O_RDONLY);
	if (!fd || fd == -1)
	{
		close(fd);
		free(buffer);
		return (0);
	}
	len = read(fd, buffer, BUFFER_SIZE);
	if (len < 0)
	{
		close(fd);
		free(buffer);
		return (0);
	}
	close(fd);
	return (len);
}

size_t	ft_fd_len(char *name, int fd_ext)
{
	char	*buffer;
	int		len;
	int		fd;

	len = 0;
	fd = 0;
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(buffer);
		return (0);
	}
	if (fd_ext != 0 && !name)
		len = ft_read(buffer, len, fd_ext);
	else
		len = ft_fd_len_suite(name, buffer, fd, len);
	if (len <= 0)
	{
		free(buffer);
		return (0);
	}
	else
		len = ft_strlen(buffer);
	free(buffer);
	return (len);
}
