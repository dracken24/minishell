/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:05:04 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/07 20:14:09 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_child_suite(t_data *data, int *fd, int nb)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	ft_find_redirect(data, nb);
	if (ft_execute_builtin(data, nb) == true)
		;
	else
		ft_exec_cmd(data, ft_execute(data, nb), nb);
}

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
		ft_child_suite(data, fd, nb);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}
