/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:55:26 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/06 00:10:00 by nadesjar         ###   ########.fr       */
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
	else if (ft_strncmp(data->cmd[nb].token[0], "exit", 5) == 0)
		ft_exit(data, "Goodbye\n", 3);
	else if (ft_strncmp(data->cmd[nb].buffer, "cd", 2) == 0)
		ft_cd(data, data->cmd[nb].token[1]);
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
	printf("TEST\n");
}

void	ft_find_redirect(t_data *data, int nb)
{
	int	i;

	i = -1;

	while (data->cmd[nb].token[++i])
	{
		// printf("REDIRET: %s\n", data->cmd[nb].token[i]);
		if (ft_strncmp(data->cmd[nb].token[i], ">>\0", 3) == 0)
			data->cmd[nb].outfile = ft_open_fd(data->cmd[nb].token[++i], 4);
		else if (ft_strncmp(data->cmd[nb].token[i], ">\0", 2) == 0)
			data->cmd[nb].outfile = ft_open_fd(data->cmd[nb].token[++i], 2);
		else if (ft_strncmp(data->cmd[nb].token[i], "<<\0", 3) == 0)
			data->cmd[nb].infile = ft_open_fd(data->cmd[nb].token[++i], 2);
		else if (ft_strncmp(data->cmd[nb].token[i], "<\0", 2) == 0)
			data->cmd[nb].infile = ft_open_fd(data->cmd[nb].token[++i], 2);
	}
	ft_redirections(&data->cmd[nb]);
	// ft_print_table(data);
}

void	ft_make_child_process(t_data *data, int nb)
{
	//pid
	// dup
	//if fork == 1 enfent
		//enter child process
		ft_find_redirect(data, nb);
		if (ft_execute_builtin(data, nb) == true)
			return ;
		else
		{
			ft_color(RED);
			printf("<%s> is not a builtin command\n", data->cmd[nb].buffer);
			ft_color(RESET);
			// ft_execute(data, nb);
			ft_exec_cmd(data, ft_execute(data, nb), nb);
			// printf("PATH: %s\n", ft_execute(data, nb));
		}
	// else
		// wait pid
}
