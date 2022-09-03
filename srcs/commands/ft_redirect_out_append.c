/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_out_append.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 12:14:11 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/01 17:12:50 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_redirect_output_append(t_cmd *cmd)
/* >> */
{
    char	*str;

	str = ft_calloc(sizeof(char), ft_fd_len(cmd->token[3], 0));
	if (!str)
	{
		free(str);
		return ;
	}
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


