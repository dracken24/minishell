/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_out_append.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:14:11 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/06 13:44:20 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



void	ft_redirections(t_cmd *cmd)
{
	int		i;
	// int		k;
	
	i = -1;
	while (cmd->token[++i])
	{
		if (ft_strncmp(cmd->token[i], ">>", 2) == 0)
		{
			ft_redirect_output_append(cmd);
			dup2(cmd->outfile, STDOUT_FILENO);
			cmd->token[i] = NULL;
			break ;
		}
		else if (ft_strncmp(cmd->token[i], ">", 1) == 0)
		{
			// printf("1\n");
			dup2(cmd->outfile, STDOUT_FILENO);
			cmd->token[i] = NULL;
			break ;
		}
		else if (ft_strncmp(cmd->token[i], "<", 1) == 0)
		{
			// boucle pour heredoc
			dup2(cmd->infile, STDIN_FILENO);
		}
	}
	// i = -1;
	// while (cmd->token[++i])
	// 	printf("TOKEN: %s\n", cmd->token[i]);
}
