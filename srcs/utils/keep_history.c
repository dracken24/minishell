/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keep_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:56:21 by nadesjar          #+#    #+#             */
/*   Updated: 2023/01/18 10:39:27 by dracken24        ###   ########.fr       */
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
	tmp = ft_calloc(sizeof(char *), 51);
	fd = ft_open_fd(ft_get_variable("HISTORY", 0), 6);
	tmp[i] = get_next_line(fd);
	if (!tmp[i])
	{
		close(fd);
		return ;
	}
	free(tmp[i]);
	while (i < 50)
	{
		tmp[i] = get_next_line(fd);
		if (!tmp[i])
			break ;
		i++;
	}
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
		if (i >= 50)
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

void	ft_save_env(char *name)
{
	char	**tmp;
	char	*path;
	int		fd;
	int		i;

	path = ft_get_variable(name, 0);
	fd = ft_open_fd(path, 1);
	tmp = ft_calloc(sizeof(char), BUFFER_SIZE);
	if (!tmp)
		ft_exit(&shell, "error calloc <ft_save_env>\n", -1);
	tmp[0] = get_next_line(fd);
	i = 0;
	while (tmp[i])
	{
		if (tmp[i])
			tmp[i][ft_strlen(tmp[i]) - 1] = '\0';
		i++;
		tmp[i] = get_next_line(fd);
	}
	ft_free_array(g_env);
	g_env = ft_remalloc(tmp, 2, 0);
	close(fd);
}
