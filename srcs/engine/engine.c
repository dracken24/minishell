/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:55:26 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/03 13:59:09 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execute_table(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_count)
	{
		ft_redirect_before(&data->cmd[i]);
		ft_execute_builtin(data, &data->cmd[i]);
		ft_redirect_after(&data->cmd[i]);
	}
}

void	ft_redirect_before(t_cmd *cmd)
{
	if (cmd->outfile)
		ft_cat_redirect(cmd);
}

void	ft_redirect_after(t_cmd *cmd)
{
	int	*fd;

	fd = ft_calloc(sizeof(int), 2);
	if (!fd)
	{
		free(fd);
		return ;
	}
	if (cmd->outfile)
		dup2(fd[1], STDOUT_FILENO);
	free(fd);
}

void	ft_execute_builtin_suite(t_data *data, t_cmd *cmd)
{
	if (ft_strncmp(cmd->buffer, "exit", 4) == 0)
		ft_exit(data, "Good bye!\n", 4);
	else if (cmd->ct == 0)
	{
		ft_color(1);
		printf("<%s> is not a builtin command\n", cmd->buffer);
		ft_color(6);
	}
}

void	ft_execute_builtin(t_data *data, t_cmd *cmd)
{
	if (ft_strncmp(cmd->buffer, "echo", 4) == 0)
	{
		if (ft_strncmp(cmd->token[1], "-n", 2) == 0)
			ft_echo(data, cmd, cmd->token[2]);
		else
			ft_echo(data, cmd, cmd->token[1]);
	}
	else if (ft_strncmp(cmd->buffer, "env", 3) == 0)
		ft_env(data, cmd);
	else if (ft_strncmp(cmd->buffer, "pwd", 3) == 0)
		ft_pwd(data, cmd);
	else if (ft_strncmp(cmd->buffer, "cd", 2) == 0)
		ft_cd(data, cmd, cmd->token[1]);
	else if (ft_strncmp(cmd->buffer, "cat", 3) == 0)
		ft_cat(cmd);
	else if (ft_strncmp(cmd->buffer, "export", 6) == 0)
		ft_export(data, cmd, cmd->token[1]);
	else if (ft_strncmp(cmd->buffer, "unset", 5) == 0)
		ft_unset(data, cmd, cmd->token[1]);
	else if (ft_strncmp(cmd->buffer, "wc", 2) == 0)
		ft_wc(cmd);
	else if (ft_strncmp(cmd->buffer, "grep", 4) == 0)
		ft_grep(cmd);
	ft_execute_builtin_suite(data, cmd);
}
