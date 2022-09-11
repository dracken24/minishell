/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:46:46 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/11 19:01:55 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_heredoc(char *limiter, char *heredoc)
{
	char	*str;
	int		fd;
	int		i;

	fd = ft_open_fd(heredoc, 2);
	if (fd == -1)
		ft_exit("Error: heredoc file not found", 1);
	str = readline("<heredoc> ");
	i = 1;
	while (str)
	{
		if (ft_strnstr(str, limiter, ft_strlen(limiter)) != 0
			&& str[ft_strlen(limiter)] == '\0')
			break ;
		else if (i != 1)
			ft_putstr_fd("\n", fd);
		ft_putstr_fd(str, fd);
		free(str);
		str = readline("<heredoc> ");
		i = 0;
	}
	close(fd);
	free(str);
}
