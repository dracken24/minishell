/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:46:46 by nadesjar          #+#    #+#             */
/*   Updated: 2022/08/17 15:20:58 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_heredoc(char *limiter)
{
	char	*str;
	int		fd;

	fd = ft_open_fd("heredoc", 2);
	if (fd == -1)
		return (false);
	str = readline("<heredoc> ");
	while (str)
	{
		if (ft_strnstr(str, limiter, ft_strlen(limiter)) != 0
			&& str[ft_strlen(limiter)] == '\0')
			break ;
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
		free(str);
		str = readline("<heredoc> ");
	}
	close(fd);
	free(str);
	return (true);
}
