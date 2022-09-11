/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/10 22:23:06 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	data;

int	main(int ac, char **argv, char **env)
{
	(void)ac;
	(void)argv;
	int		i;

	ft_init_environement(env);					// Copy environement variable in main struct
	while (1)
	{
		ft_save_env();
		i = -1;
		data.prompt = ft_get_prompt();			// Get user and path for prompt
		data.buffer = readline(data.prompt);	// Fill the buffer with user input
		free(data.prompt);						// Free the prompt for next iteration
		add_history(data.buffer);
		if (ft_is_only(data.buffer, ' '))		// Newline on empty buffer
			free(data.buffer);
		else if (ft_strncmp(data.buffer, "exit\0", 5) == 0)
			ft_quit("Good bye my friend !!!");
		else
		{
			ft_fork_main(i);
			ft_free_table();
		}
	}
}

void	ft_fork_main(int nb)
{
	pid_t	pid;
	// int		ret;

	ft_parse(); 								// tokenize the buffer
	pid = fork();
	if (pid == -1)
		ft_exit("Fork failed", 3);
	if (pid == 0)
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
	else
		waitpid(pid, NULL, 0);
}
