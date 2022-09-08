/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:04:49 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/07 20:10:35 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **arg)
{
	int i;
	int flag;

	flag = 0;
	i = 1;
	if (arg[1] && ft_strncmp(arg[1], "-n\0", 3) == 0)
	{
		flag = 1;
		i++;
	}
	while (arg[i])
	{
		if (ft_is_only(arg[i], ' '))
			i++;
		else
		{
		printf("%s", arg[i++]);
		if (arg[i])
			printf(" ");
		}
	}
	if (flag == 0)
		printf("\n");
}

void	ft_env(t_data *data)
{
	int i;

	i = -1;
	while(data->env[++i])
		printf("%s\n", data->env[i]);
}
