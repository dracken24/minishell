/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/11 11:46:09 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	data;
void	ft_save_history(void);
int	main(int ac, char **argv, char **env)
{
	int		i;

	ft_sig(ac, argv);
	ft_init_environement(env);					// Copy environement variable in main struct
	while (1)
	{
		ft_save_env("STARTDIR");
		i = -1;
		data.prompt = ft_get_prompt();			// Get user and path for prompt
		data.buffer = readline(data.prompt);	// Fill the buffer with user input
		free(data.prompt);
		// if (add_history(data.buffer) == 0) // Free the prompt for next iteration
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
