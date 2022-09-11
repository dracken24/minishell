/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:40:49 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/11 16:43:57 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_data data;

void	ft_init_suite(void)
{
	data.expand[0] = 'a';
	data.expand[1] = '\0';
	data.heredoc = 'a';
	data.buffer = NULL;
	data.prompt = NULL;
	data.cmd_count = 0;
	data.cmd = NULL;
}

void	ft_init_environement(char **env)
{
	int i;

	ft_init_suite();
	i = -1;
	data.env = ft_calloc(sizeof(char *), ft_array_size(env));
	if (data.env == NULL)
		ft_exit("Malloc Error\n", 0);
	while (env[++i])
	{
		data.env[i] = ft_strdup(env[i]);
		if (!data.env[i])
			ft_exit("Malloc Error\n", 0);
	}
	data.env[i] = ft_strjoin("STARTDIR=", ft_strjoin(getcwd(NULL, 0), "/env", 0), 0);
	ft_fd_env();
}

void	ft_fd_env(void)
{
	int		fd;
	int		i;
	char	*path;
	
	path = ft_get_variable("STARTDIR");
	fd = ft_open_fd(path, 2);
	i = -1;
	while (data.env[++i])
	{
		ft_putstr_fd(data.env[i], fd);
		ft_putchar_fd('\n', fd);
	}
	close(fd);
}

void	ft_save_env(void)
{
	char	**tmp;
	char	*path;
	int		fd;
	int		i;

	path = ft_get_variable("STARTDIR");
	fd = ft_open_fd(path, 1);
	tmp = ft_calloc(sizeof(char), 10000);
	if (!tmp)
		ft_exit("error calloc <ft_save_env>", 0);
	tmp[0] = get_next_line(fd);
	i = 0;
	while (tmp[i])
	{
		if (tmp[i])
			tmp[i][ft_strlen(tmp[i]) - 1] = '\0';
		i++;
		tmp[i] = get_next_line(fd);
	}
	ft_free_ptr(data.env);
	data.env = tmp;
	close(fd);
}
