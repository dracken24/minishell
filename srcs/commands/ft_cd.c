/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:40:45 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/07 20:10:54 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(t_data *data, char *buffer)
{
	int new;
	int old;
	int ret;

	ret = chdir(buffer);
	printf("ret = %d\n", ret);
	old = -1;
	while (data->env[++old])
	{
		if (ft_strncmp(data->env[old], "OLDPWD=", 7) == 0)
			break ;
	}
	new = -1;
	while (data->env[++new])
	{
		if (ft_strncmp(data->env[new], "PWD=", 4) == 0)
			break ;
	}
	if (ret == 0)
	{
		free (data->env[old]);
		data->env[old] = data->env[new];
		data->env[new] = ft_strjoin("PWD=", getcwd(NULL, 0), 0);
		printf("PWD = %s\n", data->env[new]);
	}
}
