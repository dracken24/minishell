/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 08:44:09 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/03 13:18:09 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_wc_flags(t_cmd *cmd, int l, int w, int c)
{
	if (!cmd->token[2])
		printf("%d %d %d %s\n", l, w, c, cmd->token[1]);
	else if (ft_strncmp(cmd->token[1], "-l", 2) == 0)
		printf("%d %s\n", l, cmd->token[2]);
	else if (ft_strncmp(cmd->token[1], "-w", 2) == 0)
		printf("%d %s\n", w, cmd->token[2]);
	else if (ft_strncmp(cmd->token[1], "-m", 2) == 0)
		printf("%d %s\n", c , cmd->token[2]);
}

char	**ft_wc_suite(t_cmd *cmd)
{
	char	**buffer;
	int		i;
	
	i = 0;
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE);
	if (!buffer)
	{
		free(buffer);
		return (NULL) ;
	}
	buffer[i] = get_next_line(cmd->infile);
	while (buffer[i])
	{
		i++;
		buffer[i] = get_next_line(cmd->infile);
	}
	return (buffer);
}

void	ft_wc(t_cmd *cmd)
{
	char	**buffer;
	int		l;
	int		j;
	int		w;
	int		c;

	buffer = ft_wc_suite(cmd);
	l = -1;
	c = 0;
	w = 0;
	while (buffer[++l])
	{
		j = -1;
		while (buffer[l][++j])
		{
			if (buffer[l][j] == ' ' || !buffer[l][j])
				w++;
		}
		w++;
		c += j;
	}
	ft_wc_flags(cmd, l, w, c);
	ft_free_ptr(buffer);
	cmd->ct = 1;
}
