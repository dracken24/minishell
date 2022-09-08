/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/08 17:17:31 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **argv, char **env)
{
	(void)ac;
	(void)argv;
	t_data	data;
	int		i;

	ft_init_environement(&data, env);			// Copy environement variable in main struct
	while (1)
	{
		i = -1;
		data.prompt = ft_get_prompt(&data);		// Get user and path for prompt
		data.buffer = readline(data.prompt);	// Fill the buffer with user input
		free(data.prompt);						// Free the prompt for next iteration
		add_history(data.buffer);
		if (ft_is_only(data.buffer, ' '))		// Newline on empty buffer
			free(data.buffer);
		else
		{
			ft_parse(&data); // tokenize the buffer
			if (ft_check_builtin(&data, 0) == 1 && data.cmd_count == 1)
			{
				ft_find_redirect(&data, 0);
				ft_execute_builtin(&data, 0);
			}
			else
				ft_fork_main(&data, i);
			ft_free_table(&data);
		}
	}
}

void	ft_fork_main(t_data *data, int nb)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_exit(data, "Fork failed", 3);
	if (pid == 0)
	{
		ft_print_table(data);				//print the table with all the tokens
		while (++nb < data->cmd_count - 1)
			ft_make_child_process(data, nb);
		ft_find_redirect(data, nb);
		ft_print_table(data);
		if (ft_execute_builtin(data, nb) == true)
			ft_exit(data, "exit fork", 3);
		else
			ft_exec_cmd(data, ft_execute(data, nb), nb);
	}
	else
		waitpid(pid, NULL, 0);
}
