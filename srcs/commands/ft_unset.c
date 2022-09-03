/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:19:48 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/03 13:17:43 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_unset(t_data *data, t_cmd *cmd, char *buffer)
{
	int	i;

	cmd->ct = 1;
	i = -1;
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], buffer, ft_strlen(buffer)) == 0
			&& data->env[i][ft_strlen(buffer)] == '=')
		{
			while (data->env[i])
			{
				data->env[i] = data->env[i + 1];
				i++;
			}
			free(data->env[i]);
			return (true);
		}
	}
	return (false);
}
