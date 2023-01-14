/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 18:29:51 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/14 07:33:04 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_data	data;

void	ft_keep_cmd_suite(char *path, int nb)
{
	int	k;

	// if (data.cmd[nb].token)
	if (data.cmd[nb].token[2] && (ft_strncmp(data.cmd[nb].token[2], "<", 1) == 0
			|| ft_strncmp(data.cmd[nb].token[2], ">", 1)) == 0)
		data.cmd[nb].token[2] = NULL;
	else if (data.cmd[nb].token[1]
		&& (ft_strncmp(data.cmd[nb].token[1], "<", 1) == 0
			|| ft_strncmp(data.cmd[nb].token[1], ">", 1)) == 0)
		data.cmd[nb].token[1] = NULL;
	if (data.ct == 0)
		data.cmd[nb].token++;
	k = 2;
	while (data.cmd[nb].token[k] && (data.cmd[nb].token[k][0] == '-'
		|| data.cmd[nb].token[k][0] == '$'))
		k++;
	if (data.cmd[nb].token[k])
		data.cmd[nb].token[k] = NULL;
	free(path);
}

void	ft_keep_cmd(int nb)
{
	int		i;
	char	*path;

	data.ct = 1;
	i = -1;
	while (data.cmd[nb].token[++i])
	{
		path = NULL;
		data.cmd[nb].token[0] = data.cmd[nb].token[i];
		path = ft_get_path(nb);
		if (path || ft_check_builtin(nb, 0) == true)
		{
			ft_keep_cmd_suite(path, nb);
			return ;
		}
		else
			data.cmd[nb].token++;
		free(path);
		data.ct = 0;
	}
}

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
