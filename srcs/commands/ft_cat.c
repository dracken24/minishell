/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 19:04:14 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/03 13:38:08 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cat_redirect(t_cmd *cmd)
{
	int	i;
	
	i = -1;
	while (cmd->token[++i])
	{
		if (ft_strncmp(cmd->token[i], ">>", 2) == 0)
		{
			ft_redirect_output_append(cmd);
			dup2(cmd->outfile, STDOUT_FILENO);
		}
		else if (ft_strncmp(cmd->token[i], ">", 1) == 0)
			dup2(cmd->outfile, STDOUT_FILENO);
	}
}

void	ft_cat_suite(t_cmd *cmd, char *str)
{
	// int	*fd;

	// fd = ft_calloc(sizeof(int), 2);
	// if (!fd)
	// {
	// 	free(fd);
	// 	return;
	// }
	// ft_cat_redirect(cmd);
	printf("%s", str);
	while (str)
	{
		free(str);
		str = get_next_line(cmd->infile);
		if (str)
			printf("%s", str);
	}
	free(str);
	// if (cmd->outfile)
	// 	dup2(fd[1], STDOUT_FILENO);
	// free(fd);
}

bool	ft_cat(t_cmd *cmd)
{
	char	*str;

	if (cmd->nbr_token == 4)
		if (ft_strncmp(cmd->token[1], cmd->token[3], ft_strlen(cmd->token[1])) == 0)
		{
			printf("cat: %s: input file is output file\n", cmd->token[3]);
			return (false);
		}
	if (!cmd->infile)
	{
		printf("error, wrong open file\n");
		return (false);
	}
	str = get_next_line(cmd->infile);
	if (!str)
	{
		printf("cat: No such file or directory\n");
		return (false);
	}
	else
		ft_cat_suite(cmd, str);
	cmd->ct = 1;
	return (true);
}
