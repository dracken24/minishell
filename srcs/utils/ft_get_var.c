/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 13:02:10 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/02 23:38:55 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// extern char **environ;

char	*ft_get_variable(t_data *data, char *buffer)
{
	char	*str;
	int		i;

	str = ft_strjoin(buffer, "=", 0);
	i = -1;
	while (data->env[++i])
	{
		if (data->env[i] && !ft_strncmp(data->env[i], str, ft_strlen(str)))
		{
			free(str);
			return (data->env[i] + ft_strlen(buffer) + 1);
		}
	}
	free(str);
	ft_color(1);
	printf("<%s> variable not exist\n", buffer);
	ft_color(6);
	return (NULL);
}

void	ft_print_variable(t_data *data, char *buffer)
{
	char	*str;
	int		i;

	str = ft_strjoin(buffer, "=", 0);
	i = -1;
	while (data->env[++i])
	{
		if (data->env[i] && !ft_strncmp(data->env[i], str, ft_strlen(str)))
		{
			free(str);
			printf("%s", data->env[i] + ft_strlen(buffer) + 1);
		}
	}
	free(str);
	ft_color(1);
	printf("<%s> variable not exist\n", buffer);
	ft_color(6);
}
