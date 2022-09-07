/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:55:26 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/06 23:10:56 by nadesjar         ###   ########.fr       */
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
}

void	ft_redirect_output_append(t_cmd *cmd)
/* >> */
{
    char	*str;

	str = get_next_line(cmd->outfile);
	while (str)
	{
		if (str)
			printf("%s", str);
		free(str);
		str = get_next_line(cmd->outfile);
	}
	free(str);
}

void	ft_find_redirect(t_data *data, int nb)
{
	int	i;

	// check si infile, outfile ou outappend != -1
	// si oui,
	// si infile > 2;  dup2(infile, 0);
	// si outfile > 2; dup2(outfile, 1);
	// si outappend > 2; dup2(outappend, 1);
	i = -1;
	while (data->cmd[nb].token[++i])
	{
		if (ft_strncmp(data->cmd[nb].token[i], ">>", 2) == 0)
		{
			data->cmd[nb].outfile = ft_open_fd(data->cmd[nb].token[++i], 4);
			ft_redirect_output_append(&data->cmd[nb]);
			dup2(data->cmd[nb].outfile, STDOUT_FILENO);
			data->cmd[nb].token[--i] = NULL;
		}
		else if (ft_strncmp(data->cmd[nb].token[i], ">", 1) == 0)
		{
			data->cmd[nb].outfile = ft_open_fd(data->cmd[nb].token[++i], 2);
			dup2(data->cmd[nb].outfile, STDOUT_FILENO);
			data->cmd[nb].token[--i] = NULL;
			// break ;
		}
		else if (ft_strncmp(data->cmd[nb].token[i], "<", 1) == 0
				&& data->cmd[nb].token[i][1] != '<')
		{
			data->cmd[nb].infile = ft_open_fd(data->cmd[nb].token[++i], 2);
			dup2(data->cmd[nb].infile, STDIN_FILENO);
		}
		// i = -1;
		// while (data->cmd[nb].token[++i])
		// 	printf("TOK: %s\n", data->cmd[nb].token[i]);
	}
}

// cat infile | wc outfile
void	ft_make_child_process(t_data *data, int nb)
{
	pid_t	pid;
	int		fd[2];
	
	if (pipe(fd) == -1)
	{
		printf("Pipe failed\n");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		printf("Fork failed\n");
		return ;
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_find_redirect(data, nb);
		if (ft_execute_builtin(data, nb) == true)
			return ;
		else
			ft_exec_cmd(data, ft_execute(data, nb), nb);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

// void	ft_make_child_process(t_data *data, int nb)
// {
// 	//pid
// 	// dup
// 	//if fork == 1 enfent
// 		//enter child process
// 		ft_find_redirect(data, nb);
// 		if (ft_execute_builtin(data, nb) == true)
// 		{
// 			return ;
// 		}
// 		else
// 		{
// 			ft_color(RED);
// 			printf("<%s> is not a builtin command\n", data->cmd[nb].buffer);
// 			ft_color(RESET);
// 			ft_execute(data, nb);
// 			ft_exec_cmd(data, ft_execute(data, nb), nb);
// 			// printf("PATH: %s\n", ft_execute(data, nb));
// 		}
// 	// else
// 		// wait pid
// }
