/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:55:26 by nadesjar          #+#    #+#             */
/*   Updated: 2022/10/27 16:10:15 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clear_heredoc(int nb);
void	ft_keep_cmd(int nb);

extern t_data data;

bool	ft_execute_builtin(int nb)
{
	if (ft_strncmp(data.cmd[nb].token[0], "echo", 4) == 0)
		ft_echo(data.cmd[nb].token);
	else if (ft_strncmp(data.cmd[nb].token[0], "env", 3) == 0)
		ft_env();
	else if (ft_strncmp(data.cmd[nb].token[0], "export", 6) == 0)
		ft_export(data.cmd[nb].token[1], nb);
	else if (ft_strncmp(data.cmd[nb].token[0], "unset\0", 6) == 0)
		ft_unset(data.cmd[nb].token[1], nb);
	else if (ft_strncmp(data.cmd[nb].token[0], "pwd", 3) == 0)
		printf("%s\n", ft_get_variable("PWD"));
	else if (ft_strncmp(data.cmd[nb].buffer, "cd", 2) == 0)
		ft_cd(data.cmd[nb].token[1]);
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

void	ft_find_redirect_suite(int nb, int i)
{
	if (ft_strncmp(data.cmd[nb].token[i], "<", 1) == 0
		&& data.cmd[nb].token[i][1] != '<')
	{
		if (data.cmd[nb].fd_in)
			close(data.cmd[nb].fd_in);
		data.cmd[nb].fd_in = ft_open_fd(data.cmd[nb].token[++i], 1);
		dup2(data.cmd[nb].fd_in, STDIN_FILENO);
	}
	if (ft_strncmp(data.cmd[nb].token[i], ">>", 2) == 0)
	{
		if (data.cmd[nb].fd_out)
			close(data.cmd[nb].fd_out);
		data.cmd[nb].fd_out = ft_open_fd(data.cmd[nb].token[++i], 6);
		dup2(data.cmd[nb].fd_out, STDOUT_FILENO);
	}
	else if (ft_strncmp(data.cmd[nb].token[i], ">", 1) == 0)
	{
		if (data.cmd[nb].fd_out)
			close(data.cmd[nb].fd_out);
		data.cmd[nb].fd_out = ft_open_fd(data.cmd[nb].token[++i], 2);
		dup2(data.cmd[nb].fd_out, STDOUT_FILENO);
	}
}

void	ft_find_redirect(int nb)
{
	int		i;

	i = -1;
	while (data.cmd[nb].token[++i])
		ft_find_redirect_suite(nb, i);
	// ft_print_table();
	ft_keep_cmd(nb);
	// ft_print_table();
	ft_clean_token(data.cmd[nb].token);
	// ft_print_table();
	ft_clear_heredoc(nb);
	// ft_print_table();
}

void	ft_clear_heredoc(int nb)
{
	int		i;

	i = -1;
	while (data.cmd[nb].token[++i])
	{
		if (ft_strnstr_ret_tofind(data.cmd[nb].token[i], "heredoc",
				ft_strlen(data.cmd[nb].token[i]))
			&& data.cmd[nb].token[i - 1][0] == '<')
		{
			data.cmd[nb].token[i] = NULL;
		}
	}
}
