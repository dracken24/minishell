/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keep_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:56:21 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/15 19:32:22 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_data data;

void	ft_moove_history(void)
{
	char	**tmp;
	int		fd;
	int		i;

	i = 0;
	tmp = ft_calloc(sizeof(char *), 24);
	fd = ft_open_fd(ft_get_variable("HISTORY"), 6);
	tmp[i] = get_next_line(fd);
	if (!tmp[i])
	{
		close(fd);
		return ;
	}
	free(tmp[i]);
	while (i < 20)
	{
		tmp[i] = get_next_line(fd);
		if (!tmp[i])
			break ;
		i++;
	}
	if (tmp[i])
		free(tmp[i]);
	tmp[i] = ft_strjoin(data.buffer, "\n", 0);
	close (fd);
	fd = ft_open_fd(ft_get_variable("HISTORY"), 2);
	i = -1;
	while (tmp[++i])
		ft_putstr_fd(tmp[i], fd);
	close(fd);
	ft_free_ptr(tmp);
}

bool	ft_refresh_history(int fd)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = get_next_line(fd);
	while (tmp)
	{
		i++;
		if (i >= 20)
		{
			close(fd);
			ft_moove_history();
			free(tmp);
			return (true);
		}
		free(tmp);
		tmp = get_next_line(fd);
	}
	return (false);
}

void	ft_save_history(void)
{
	int		fd;

	if (ft_is_only(data.buffer, ' ') == true || ft_strncmp(data.buffer, "\n", 1) == 0)
		return ;
	fd = ft_open_fd(ft_get_variable("HISTORY"), 6);
	if(ft_refresh_history(fd) == true)
		return ;
	ft_putstr_fd(data.buffer, fd);
	ft_putstr_fd("\n", fd);
	close(fd);
}

void	ft_add_history(char *name)
{
	char	*tmp;
	int		fd;
	int		i;

	fd = ft_open_fd(ft_get_variable(name), 4);
	tmp = get_next_line(fd);
	i = 0;
	while (tmp)
	{
		add_history(tmp);
		free(tmp);
		i++;
		tmp = get_next_line(fd);
	}
	free(tmp);
	close(fd);
}
