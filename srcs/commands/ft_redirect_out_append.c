/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_out_append.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:14:11 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/05 20:37:54 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_redirect_output_append(t_cmd *cmd)
/* >> */
{
    char	*str;

	str = get_next_line(cmd->outfile);
	while (str)
	{
		if (str)
			printf("%s", str);
		free(str);
		str = get_next_line(cmd->outfile);
	}
	free(str);
}

void	ft_redirections(t_cmd *cmd)
{
	int	i;
	
	i = -1;
	while (cmd->token[++i])
	{
		if (ft_strncmp(cmd->token[i], ">>\0", 3) == 0)
		{
			ft_redirect_output_append(cmd);
			dup2(cmd->outfile, STDOUT_FILENO);
			// cmd->token[i][0] = '\0';
			// cmd->token[i + 1][0] = '\0';
		}
		else if (ft_strncmp(cmd->token[i], ">\0", 2) == 0)
		{
			dup2(cmd->outfile, STDOUT_FILENO);
			// cmd->token[i][0] = '\0';
			// cmd->token[i + 1][0] = '\0';
		}
		// if (ft_strncmp(cmd->token[i], "<<\0", 3) == 0)
		// {
		// 	ft_redirect_output_append(cmd, cmd->token[++i]);
		// 	dup2(cmd->infile, STDIN_FILENO);
		// }
		// else if (ft_strncmp(cmd->token[i], "<\0", 2) == 0)
		// 	dup2(cmd->infile, STDIN_FILENO);
		
	}
	i = -1;
	while (cmd->token[++i])
		printf("TOKEN: %s\n", cmd->token[i]);
}
