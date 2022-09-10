/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 13:02:10 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/10 11:37:19 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_data data;

void	ft_print_table(void)
{
	int	i;
	int	j;

	i = 0;
	ft_color(RED);
	dprintf(2, "---------- COMAND TABLE ----------\n");
	while (i < data.cmd_count)
	{
		j = 0;
		ft_color(CYAN);
		dprintf(2, "[cmd %d]", i);
		while (data.cmd[i].token[j])
		{
			ft_color(YELLOW);
			dprintf(2, "[%s]", data.cmd[i].token[j]);
			j++;
		}
		dprintf(2, "\n");
		i++;
	}
	ft_color(RED);
	dprintf(2, "---------------END----------------\n");
	ft_color(RESET);
}

char	*ft_get_variable(char *buffer)
{
	int		i;

	i = -1;
	while (data.env[++i])
	{
		if (ft_strncmp(data.env[i], buffer, ft_strlen(buffer)) == 0)
		{
			if (data.env[i][ft_strlen(buffer)] == '=')
				return (data.env[i] + (ft_strlen(buffer) + 1));
		}
	}
	buffer[0] = '\0';
	return (buffer);
}

char	*ft_get_prompt(void)
{
	char	*prompt;

	prompt = ft_strjoin("\033[0;32m", ft_get_variable("USER"), 0);
	prompt = ft_strjoin(prompt, "@", 1);
	prompt = ft_strjoin(prompt, "Minishell", 1);
	prompt = ft_strjoin(prompt, ": ", 1);
	prompt = ft_strjoin(prompt, "\033[0;34m", 1);
	prompt = ft_strjoin(prompt, ft_get_variable("PWD"), 1);
	prompt = ft_strjoin(prompt, "> ", 1);
	prompt = ft_strjoin(prompt, "\033[0m", 1);
	return (prompt);
}

bool	ft_check_builtin(int nb)
{
	if (ft_strncmp(data.cmd[nb].token[0], "echo", 4) == 0)
		return (true);
	else if (ft_strncmp(data.cmd[nb].token[0], "env", 3) == 0)
		return (true);
	else if (ft_strncmp(data.cmd[nb].token[0], "export", 6) == 0)
		return (true);
	else if (ft_strncmp(data.cmd[nb].token[0], "unset", 5) == 0)
		return (true);
	else if (ft_strncmp(data.cmd[nb].token[0], "pwd", 3) == 0)
		return (true);
	else if (ft_strncmp(data.cmd[nb].buffer, "cd", 2) == 0)
		return (true);
	else if (ft_strncmp(data.cmd[nb].token[0], "exit", 4) == 0)
		return (true);
	else
		return (false);
	return (true);
}
