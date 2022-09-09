/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 13:02:10 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/08 21:31:54 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_table(t_data *data)
{
	int	i;
	int	j;

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
	ft_color(RESET);
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

	prompt = ft_strjoin("\033[0;32m", ft_get_variable(data, "USER"), 0);
	prompt = ft_strjoin(prompt, "@", 1);
	prompt = ft_strjoin(prompt, "Minishell", 1);
	prompt = ft_strjoin(prompt, ": ", 1);
	prompt = ft_strjoin(prompt, "\033[0;34m", 1);
	prompt = ft_strjoin(prompt, ft_get_variable(data, "PWD"), 1);
	prompt = ft_strjoin(prompt, "> ", 1);
	prompt = ft_strjoin(prompt, "\033[0m", 1);
	return (prompt);
}

bool	ft_check_builtin(t_data *data, int nb)
{
	if (ft_strncmp(data->cmd[nb].token[0], "echo", 4) == 0)
		return (true);
	else if (ft_strncmp(data->cmd[nb].token[0], "env", 3) == 0)
		return (true);
	else if (ft_strncmp(data->cmd[nb].token[0], "export", 6) == 0)
		return (true);
	else if (ft_strncmp(data->cmd[nb].token[0], "unset", 5) == 0)
		return (true);
	else if (ft_strncmp(data->cmd[nb].token[0], "pwd", 3) == 0)
		return (true);
	else if (ft_strncmp(data->cmd[nb].buffer, "cd", 2) == 0)
		return (true);
	else if (ft_strncmp(data->cmd[nb].token[0], "exit", 4) == 0)
		return (true);
	else
		return (false);
	return (true);
}
