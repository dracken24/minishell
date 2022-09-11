/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:40:49 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/10 21:12:04 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_data data;

void	ft_init_environement(char **env)
{
	int i;

	data.expand[0] = 'a';
	data.expand[1] = '\0';
	data.heredoc[0] = 'a';
	data.heredoc[1] = '\0';
	data.buffer = NULL;
	data.prompt = NULL;
	data.cmd_count = 0;
	data.cmd = NULL;
	i = 0;
	data.env = ft_calloc(sizeof(char *), ft_array_size(env));
	if (data.env == NULL)
		ft_exit("Malloc Error\n", 0);
	while (env[i])
	{
		data.env[i] = ft_strdup(env[i]);
		if (!data.env[i])
			ft_exit("Malloc Error\n", 0);
		i++;
	}
	i = 0;
	while (env[i])
	{
		data.env[i] = ft_strdup(env[i]);
		if (!data.env[i])
			ft_exit("Malloc Error\n", 0);
		i++;
	}
	ft_fd_env();
	// ft_save_env();
}

void	ft_fd_env(void)
{
	int		fd;
	int		i;

	fd = ft_open_fd("envi", 3);
	i = -1;
	while (data.env[++i])
	{
		ft_putstr_fd(data.env[i], fd);
		if (data.env[i + 1])
			ft_putchar_fd('\n', fd);
	}
}

void	ft_save_env(void)
{
	char	**tmp;
	int		fd;
	int		i;

	fd = ft_open_fd("envi", 1);
	tmp = ft_calloc(sizeof(char), ft_fd_len("envi", 0) + 1);
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
}
