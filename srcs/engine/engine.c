/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:55:26 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/10 11:40:14 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	ft_execute(t_data *data, int nb);
extern t_data data;

bool	ft_execute_builtin(int nb)
{
	if (ft_strncmp(data.cmd[nb].token[0], "echo", 4) == 0)
		ft_echo(data.cmd[nb].token);
	else if (ft_strncmp(data.cmd[nb].token[0], "env", 3) == 0)
		ft_env();
	else if (ft_strncmp(data.cmd[nb].token[0], "export", 6) == 0)
		ft_export(data.cmd[nb].token[1]);
	else if (ft_strncmp(data.cmd[nb].token[0], "unset\0", 6) == 0)
		ft_unset(data.cmd[nb].token[1]);
	else if (ft_strncmp(data.cmd[nb].token[0], "pwd", 3) == 0)
		printf("%s\n", ft_get_variable("PWD"));
	else if (ft_strncmp(data.cmd[nb].buffer, "cd", 2) == 0)
		ft_cd(data.cmd[nb].token[1]);
	else if (ft_strncmp(data.cmd[nb].token[0], "exit", 4) == 0)
		ft_exit("Goodbye\n", 3);
	else
		return (false);
	return (true);
}

void	ft_exec_cmd(char *cmd_path, int nb)
{
	
	if (execve(cmd_path, data.cmd[nb].token, data.env) == -1)
	{
		printf("minishell: %s: command not found\n", data.cmd[nb].token[0]);
		return ;
	}
}

// void	ft_redirect_output_append(t_cmd *cmd)
// /* >> */
// {
// 	char	*str;

// 	str = get_next_line(cmd->fd_out);
// 	while (str)
// 	{
// 		if (str)
// 			printf("%s", str);
// 		free(str);
// 		str = get_next_line(cmd->fd_out);
// 	}
// 	free(str);
// }

void	ft_find_redirect(int nb)
{
	int	i;

	i = -1;
	while (data.cmd[nb].token[++i])
	{
		if (ft_strncmp(data.cmd[nb].token[i], "<", 1) == 0
			&& data.cmd[nb].token[i][1] != '<')
		{
			data.cmd[nb].fd_in = ft_open_fd(data.cmd[nb].token[++i], 1);
			dup2(data.cmd[nb].fd_in, STDIN_FILENO);
			if (data.cmd[nb].token[0][0] != '<')
				data.cmd[nb].token[--i] = NULL;
			else
			{
				data.cmd[nb].token++;
				data.cmd[nb].token++;
			}
			i += 2;
		}
		if (ft_strncmp(data.cmd[nb].token[i], ">>", 2) == 0)
		{
			data.cmd[nb].fd_out = ft_open_fd(data.cmd[nb].token[++i], 6);
			dup2(data.cmd[nb].fd_out, STDOUT_FILENO);
			data.cmd[nb].token[--i] = NULL;
		}
		else if (ft_strncmp(data.cmd[nb].token[i], ">", 1) == 0)
		{
			data.cmd[nb].fd_out = ft_open_fd(data.cmd[nb].token[++i], 2);
			dup2(data.cmd[nb].fd_out, STDOUT_FILENO);
			data.cmd[nb].token[--i] = NULL;
		}
		// i = -1;
		// while (data.cmd[nb].token[++i])
		// 	printf("TOK: %s\n", data.cmd[nb].token[i]);
	}
	ft_clean_token(data.cmd[nb].token);
}
