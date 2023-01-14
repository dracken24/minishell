#include "../includes/libft.h"
#include <limits.h>

size_t	ft_slen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchrr(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (c == '\0')
		return ((char *)&str[ft_slen(str)]);
	while (str[i] != '\0')
	{
		if (str[i] == (char) c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoinn(char *save_str, char *buff)
{
	size_t	i;
	size_t	k;
	char	*str;

	if (!save_str)
	{
		save_str = malloc(1 * sizeof(char));
		save_str[0] = '\0';
	}
	if (!save_str || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_slen(save_str) + ft_slen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	k = 0;
	if (save_str)
		while (save_str[++i] != '\0')
			str[i] = save_str[i];
	while (buff[k] != '\0')
		str[i++] = buff[k++];
	str[i++] = '\0';
	free(save_str);
	return (str);
}

char	*ft_get_line(char *save_str)
{
	int		i;
	char	*str;

	i = 0;
	if (!save_str[i])
		return (NULL);
	while (save_str[i] && save_str[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (save_str[i] && save_str[i] != '\n')
	{
		str[i] = save_str[i];
		i++;
	}
	if (save_str[i] == '\n')
	{
		str[i] = save_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_get_nline(char *save_str)
{
	int		i;
	int		k;
	char	*str;

	i = 0;
	while (save_str[i] && save_str[i] != '\n')
		i++;
	if (!save_str[i])
	{
		free (save_str);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_slen(save_str) - i + 1));
	if (!str)
		return (NULL);
	i++;
	k = 0;
	while (save_str[i] != '\0')
		str[k++] = save_str[i++];
	str[k] = '\0';
	free (save_str);
	return (str);
}

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