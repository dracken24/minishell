/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 13:02:10 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/05 12:28:12 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_table(t_data *data)
{
	int i;
	int j;
	
	i = 0;
	ft_color(RED);
	printf("---------- COMAND TABLE ----------\n");
	while (i < data->cmd_count)
	{
		j = 0;
		ft_color(CYAN);
		printf("[cmd %d]", i);
		while (data->cmd[i].token[j])
		{
			ft_color(YELLOW);
			printf("[%s]", data->cmd[i].token[j]);
			j++;
		}
		printf("\n");
		i++;
	}
	ft_color(RED);
	printf("---------------END----------------\n");
	ft_color(WHITE);
}

char	*ft_get_variable(t_data *data, char *buffer)
{
	int		i;
	i = -1;
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], buffer, ft_strlen(buffer)) == 0)
		{
			if (data->env[i][ft_strlen(buffer)] == '=')
				return (data->env[i] + (ft_strlen(buffer) + 1));
		}
	}
	buffer[0] = '\0';
	return (buffer);
}

char	*ft_get_prompt(t_data *data)
{
	char	*prompt;

	prompt = ft_strjoin("\033[0;32m", ft_get_variable(data, "USER") , 0);
	prompt = ft_strjoin(prompt, "@", 1);
	prompt = ft_strjoin(prompt, "Minishell", 1);
	prompt = ft_strjoin(prompt, ": ", 1);
	prompt = ft_strjoin(prompt, "\033[0;34m", 1);
	prompt = ft_strjoin(prompt, ft_get_variable(data, "PWD"), 1);
	prompt = ft_strjoin(prompt, "> ", 1);
	prompt = ft_strjoin(prompt, "\033[0m", 1);
	return (prompt);
}

// char	*ft_get_variable(t_data *data, char *buffer)
// {
// 	char	*str;
// 	int		i;

// 	str = ft_strjoin(buffer, "=", 0);
// 	i = -1;
// 	while (data->env[++i])
// 	{
// 		if (data->env[i] && !ft_strncmp(data->env[i], str, ft_strlen(str)))
// 		{
// 			free(str);
// 			return (data->env[i] + ft_strlen(buffer) + 1);
// 		}
// 	}
// 	free(str);
// 	ft_color(1);
// 	printf("<%s> variable not exist\n", buffer);
// 	ft_color(6);
// 	return (NULL);
// }

// void	ft_print_variable(t_data *data, char *buffer)
// {
// 	char	*str;
// 	int		i;

// 	str = ft_strjoin(buffer, "=", 0);
// 	i = -1;
// 	while (data->env[++i])
// 	{
// 		if (data->env[i] && !ft_strncmp(data->env[i], str, ft_strlen(str)))
// 		{
// 			free(str);
// 			printf("%s", data->env[i] + ft_strlen(buffer) + 1);
// 		}
// 	}
// 	free(str);
// 	ft_color(1);
// 	printf("<%s> variable not exist\n", buffer);
// 	ft_color(6);
// }
