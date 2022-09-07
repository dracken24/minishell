/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/06 23:21:11 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **argv, char **env)
{
	(void)ac;
	(void)argv;
	t_data	data;
	// pid_t	pid;
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
			ft_parse(&data);					//tokenize the buffer
			// ft_print_table(&data);			//print the table with all the tokens
			while (++i < data.cmd_count - 1)
				ft_make_child_process(&data, i);
			// pid = fork();
			// if (pid == 0)
			// {
			ft_find_redirect(&data, i);
			if (ft_execute_builtin(&data, i) == true)
				continue ;
			else
				ft_exec_cmd(&data, ft_execute(&data, i), i);
			// }
			// else
				// waitpid(pid, NULL, 0);
			ft_free_table(&data);				// Free the table for next iteration
		}
	}
}
