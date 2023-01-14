/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keep_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:56:21 by nadesjar          #+#    #+#             */
/*   Updated: 2023/01/13 23:55:39 by dracken24        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char	**g_env;
extern t_shell shell;

void	ft_moove_history(void)
{
	char	**tmp;
	int		fd;
	int		i;

	i = 0;
	tmp = ft_calloc(sizeof(char *), 24);
	fd = ft_open_fd(ft_get_variable("HISTORY", 0), 6);
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
	tmp[i] = ft_strjoin(shell.buffer, "\n", 0);
	close (fd);
	fd = ft_open_fd(ft_get_variable("HISTORY", 0), 2);
	i = -1;
	while (tmp[++i])
		ft_putstr_fd(tmp[i], fd);
	close(fd);
	ft_free_array(tmp);
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

	if (ft_is_only(shell.buffer, ' ') == true || ft_strncmp(shell.buffer, "\n", 1) == 0)
		return ;
	fd = ft_open_fd(ft_get_variable("HISTORY", 0), 6);
	if(ft_refresh_history(fd) == true)
		return ;
	ft_putstr_fd(shell.buffer, fd);
	ft_putstr_fd("\n", fd);
	close(fd);
}

void	ft_add_history(char *name)
{
	char	*tmp;
	int		fd;
	int		i;

	fd = ft_open_fd(ft_get_variable(name , 0), 4);
	tmp = get_next_line(fd);
	i = 0;
	while (tmp)
	{
		tmp[ft_strlen(tmp) - 1] = '\0';
		add_history(tmp);
		free(tmp);
		i++;
		tmp = get_next_line(fd);
	}
	free(tmp);
	close(fd);
}
