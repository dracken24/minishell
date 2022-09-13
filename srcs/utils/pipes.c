/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:05:04 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/13 12:04:17 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_data data;

void	ft_child_suite(int *fd, int nb)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	ft_find_redirect(nb);
	if (ft_execute_builtin(nb) == true)
		ft_exit("", 3);
	else
		ft_exec_cmd(ft_get_path(nb), nb);
}

void	ft_make_child_process(int nb)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		printf("Pipe failed\n");
		return ;
	}
	data.pid[nb] = fork();
	if (data.pid[nb] == -1)
	{
		printf("Fork failed\n");
		return ;
	}
	if (data.pid[nb] == 0)
		ft_child_suite(fd, nb);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

void	ft_fork_main_suite(int nb)
{
	while (++nb < data.cmd_count - 1)
		ft_make_child_process(nb);
	ft_find_redirect(nb);
	if (ft_execute_builtin(nb) == true)
		ft_exit("exit fork", 3);
	else
		ft_exec_cmd(ft_get_path(nb), nb);
	nb = -1;
	while (++nb < data.cmd_count - 1)
		waitpid(data.pid[nb], NULL, 0);
}

void	ft_fork_main(int nb)
{
	pid_t	pid;

	ft_parse();
	if (data.cmd_count == 1 && (ft_check_builtin(0, 0) == true
			|| ft_check_builtin(0, 0) == true))
	{
		ft_find_redirect(0);
		ft_execute_builtin(0);
		return ;
	}
	pid = fork();
	if (pid == -1)
		ft_exit("Fork failed", 2);
	if (pid == 0)
		ft_fork_main_suite(nb);
	else
		waitpid(pid, NULL, 0);
}
