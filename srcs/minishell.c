/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/07 12:36:45 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_fork_main(t_data *data, int nb);

int	main(int ac, char **argv, char **env)
{
	(void)ac;
	(void)argv;
	t_data	data;
	pid_t pid;
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
			pid = fork();
			if (pid == -1)
				ft_exit(&data, "Fork failed", 3);
			if (pid == 0)
			{
				dprintf(2, "1\n");
				ft_parse(&data);					//tokenize the buffer
				// ft_print_table(&data);			//print the table with all the tokens
				while (++i < data.cmd_count - 1)
					ft_make_child_process(&data, i);
				ft_find_redirect(&data, i);
				if (ft_execute_builtin(&data, i) == true)
					continue ;
				else
					ft_exec_cmd(&data, ft_execute(&data, i), i);
			}
			else
				waitpid(pid, NULL, 0);
		}
		ft_free_table(&data);				// Free the table for next iteration
	}
}

void	ft_fork_main(t_data *data, int nb)
{

}

// int	main(void)
// {
// 	t_data		data;
// 	pid_t		pid;
// 	int			i;

// 	ft_init_environement(&data, environ);			// Copy environement variable in main struct
// 	while (1)
// 	{
// 		i = -1;
// 		data.prompt = ft_get_prompt(&data);		// Get user and path for prompt
// 		data.buffer = readline(data.prompt);	// Fill the buffer with user input
// 		free(data.prompt);						// Free the prompt for next iteration
// 		add_history(data.buffer);
// 		if (ft_is_only(data.buffer, ' '))		// Newline on empty buffer
// 			free(data.buffer);
// 		else
// 		{
// 			pid = fork();
// 			if (pid == -1)
// 				ft_exit(&data, "Fork failed", 3);
// 			if (pid == 0)
// 				ft_fork_main(&data, i);
// 			else
// 				waitpid(pid, NULL, 0);
// 		}
// 		ft_free_table(&data);				// Free the table for next iteration
// 	}
// }

// void	ft_fork_main(t_data *data, int nb)
// {
// 	ft_parse(data); // tokenize the buffer
// 	// ft_print_table(&data);			//print the table with all the tokens
// 	while (++nb < data->cmd_count - 1)
// 		ft_make_child_process(data, nb);
// 	ft_find_redirect(data, nb);
// 	if (ft_execute_builtin(data, nb) == true)
// 		return ;
// 	else
// 		ft_exec_cmd(data, ft_execute(data, nb), nb);
// }
