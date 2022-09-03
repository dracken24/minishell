/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:40:49 by nadesjar          #+#    #+#             */
/*   Updated: 2022/08/27 14:03:41 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char **environ;

void	ft_copy_env(t_data *data, char **env)
{
	int		i;

	i = 0;
	data->env = ft_calloc(sizeof(char *), ft_array_size(env));
	if (data->env == NULL)
		ft_exit(data, "Malloc error\n", 0);
	while (environ[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			ft_exit(data, "Malloc error\n", 0);
		i++;
	}
}

void	ft_init_environement(t_data *data, char **env)
{
	data->buffer = NULL;
	data->prompt = NULL;
	data->cmd_count = 0;
	data->cmd = NULL;
	ft_copy_env(data, env);
}
