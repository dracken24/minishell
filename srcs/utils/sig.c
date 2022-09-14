/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 07:29:07 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/14 07:29:45 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_data data;

void	ft_sig(int ac, char **argv)
{
	(void)ac;
	(void)argv; 
	signal(SIGINT, handle_sigint);
	signal(SIGSEGV, handle_sigint);
	signal(SIGQUIT, handle_sigint);
}

void	handle_sigint(int sig)
{
	// printf("SIG: %d\n", sig);
	if (sig == SIGINT)
	{
		// if (data.cmd[0].token[0])
			// ft_free_table();
		data.prompt = ft_get_prompt();
		printf("\n%s", data.prompt);
		// free(data.prompt);
	}
	else if (sig == SIGSEGV)
	{
		// ft_free_table();
		// ft_free_ptr(data.env);
		exit(1);
	}
	else if (sig == SIGQUIT)
	{
		return ;
	}
}
