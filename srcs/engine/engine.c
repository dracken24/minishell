/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:55:26 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/09 11:46:53 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	ft_execute(t_data *data, int nb);

bool	ft_execute_builtin(t_data *data, int nb)
{
	if (ft_strncmp(data->cmd[nb].token[0], "echo", 4) == 0)
		ft_echo(data->cmd[nb].token);
	else if (ft_strncmp(data->cmd[nb].token[0], "env", 3) == 0)
		ft_env(data);
	else if (ft_strncmp(data->cmd[nb].token[0], "export", 6) == 0)
		ft_export(data, data->cmd[nb].token[1]);
	else if (ft_strncmp(data->cmd[nb].token[0], "unset", 5) == 0)
		ft_unset(data, data->cmd[nb].token[1]);
	else if (ft_strncmp(data->cmd[nb].token[0], "pwd", 3) == 0)
		printf("%s\n", ft_get_variable(data, "PWD"));
	else if (ft_strncmp(data->cmd[nb].buffer, "cd", 2) == 0)
		ft_cd(data, data->cmd[nb].token[1]);
	else if (ft_strncmp(data->cmd[nb].token[0], "exit", 4) == 0)
		ft_exit(data, "Goodbye\n", 3);
	else
		return (false);
	return (true);
}

void	ft_exec_cmd(t_data *data, char *cmd_path, int nb)
{
	
	if (execve(cmd_path, data->cmd[nb].token, data->env) == -1)
	{
		printf("minishell: %s: command not found\n", data->cmd[nb].token[0]);
		return ;
	}
}

void	ft_redirect_output_append(t_cmd *cmd)
/* >> */
{
	char	*str;

	str = get_next_line(cmd->fd_out);
	while (str)
	{
		if (str)
			printf("%s", str);
		free(str);
		str = get_next_line(cmd->fd_out);
	}
	free(str);
}

void	ft_find_redirect(t_data *data, int nb)
{
	int	i;

	i = -1;
	while (data->cmd[nb].token[++i])
	{
		if (ft_strncmp(data->cmd[nb].token[i], ">>", 2) == 0)
		{
			data->cmd[nb].fd_out = ft_open_fd(data->cmd[nb].token[++i], 4);
			ft_redirect_output_append(&data->cmd[nb]);
			dup2(data->cmd[nb].fd_out, STDOUT_FILENO);
			data->cmd[nb].token[--i] = NULL;
		}
		else if (ft_strncmp(data->cmd[nb].token[i], ">", 1) == 0)
		{
			data->cmd[nb].fd_out = ft_open_fd(data->cmd[nb].token[++i], 2);
			dup2(data->cmd[nb].fd_out, STDOUT_FILENO);
			data->cmd[nb].token[--i] = NULL;
		}
		else if (ft_strncmp(data->cmd[nb].token[i], "<", 1) == 0
			&& data->cmd[nb].token[i][1] != '<')
		{
			data->cmd[nb].fd_in = ft_open_fd(data->cmd[nb].token[++i], 1);
			dup2(data->cmd[nb].fd_in, STDIN_FILENO);
			data->cmd[nb].token[--i] = NULL;
		}
		// i = -1;
		// while (data->cmd[nb].token[++i])
		// 	printf("TOK: %s\n", data->cmd[nb].token[i]);
	}
	ft_clean_token(data, data->cmd[nb].token);
}
