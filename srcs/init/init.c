/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:40:49 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/08 15:54:30 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_environement(t_data *data, char **env)
{
	int i;

	data->expand[0] = 'a';
	data->expand[1] = '\0';
	data->heredoc[0] = 'a';
	data->heredoc[1] = '\0';
	data->buffer = NULL;
	data->prompt = NULL;
	data->cmd_count = 0;
	data->cmd = NULL;
	i = 0;
	data->env = ft_calloc(sizeof(char *), ft_array_size(env));
	if (data->env == NULL)
		ft_exit(data, "Malloc Error\n", 0);
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			ft_exit(data, "Malloc Error\n", 0);
		i++;
	}
}
