/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:40:45 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/03 13:14:39 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//path absolue
//export PATH=$PATH:/usr/local/bin

bool	ft_change_dir(t_data *data, char *buffer, int i, int k)
{
	char	*tmp;
	
	if (chdir(buffer) >= 0)
	{
		tmp = ft_calloc(sizeof(char), BUFFER_SIZE);
		if (!tmp)
			return (false);
		free(data->env[k]);
		data->env[k] = ft_strjoin("OLD", data->env[i], 0);
		free(data->env[i]);
		data->env[i] = ft_strjoin("PWD", ft_strjoin("=", getcwd(tmp, BUFFER_SIZE), 0), 0);
		free(tmp);
		return (true);
	}
	return (false);
}

bool	ft_cd(t_data *data, t_cmd *cmd, char *buffer)
{
	bool	ret;
	int		i;
	int		k;

	ret = false;
	i = 0;
	while (data->env[i] && ft_strncmp(data->env[i], "PWD=", 4))
		i++;
	k = 0;
	while (data->env[k] && ft_strncmp(data->env[k], "OLDPWD=", 7))
		k++;
	if (access(buffer, F_OK | X_OK) == 0)
		ret = ft_change_dir(data, buffer, i, k);
	else
	{
		printf("Error, wrong directory\n");
		return (false);
	}
	cmd->ct = 1;
	return (ret);
}
