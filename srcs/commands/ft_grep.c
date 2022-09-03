/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:46:51 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/03 13:18:35 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_grep_color(char *str, char *sep, size_t len)
{
	int	i;
	int	k;
	int	s;

	i = -1;
	while (str[++i])
	{
		k = -1;
		s = i - 1;
		while (str[++s] && sep[++k] && str[s] == sep[k])
			if (k == (int)len -1)
			{
				ft_color(1);
				printf("%s", sep);
				ft_color(8);
				i = s + 1;
			}
		printf("%c", str[i]);
	}
}

void	ft_grep(t_cmd *cmd)
{
	char	*str;
	
	cmd->ct = 1;
	if (cmd->infile == -1)
	{
		printf("grep: %s: No such file or directory\n", cmd->token[1]);
		return ;
	}
	str = get_next_line(cmd->infile);
	while (str)
	{
		if (ft_strnstr(str, cmd->token[1], ft_strlen(str)))
			ft_print_grep_color(str, cmd->token[1], ft_strlen(cmd->token[1]));
		str = get_next_line(cmd->infile);
	}
	free(str);
}
