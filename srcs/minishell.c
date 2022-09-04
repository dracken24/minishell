/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/03 22:40:08 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// extern char **environ;

int	main(int ac, char **argv, char **env)
{
	(void)ac;
	(void)argv;
	t_data data;

	ft_init_environement(&data, env);// Copy global environ variable to heap
	while (1)
	{
		data.prompt = ft_get_prompt(&data);// Get user and path for prompt
		data.buffer = readline(data.prompt);// Fill the buffer with user input
		free(data.prompt);// Free the prompt for next iteration
		add_history(data.buffer);
		if (ft_is_only_space(data.buffer))// Newline on empty buffer
			continue ;
		else
		{
			ft_parse(&data);//tokenize the buffer
		}
		ft_free_pars(&data);
	}
	return (0);
}

void	ft_free_pars(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_count)
	{
		if (data->cmd[i].infile)
			close(data->cmd[i].infile);
		if (data->cmd[i].outfile)
			close(data->cmd[i].outfile);
	}
	free(data->buffer); // Free buffer for next iteration
	free(data->cmd);	   // Free cmd for next iteration
}
