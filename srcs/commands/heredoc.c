/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:46:46 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/11 22:40:38 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	ft_heredoc(char *limiter, char *heredoc)
// {
// 	char	*str;
// 	int		fd;

// 	fd = ft_open_fd(heredoc, 2); // open file
// 	if (fd == -1)
// 		ft_exit("Error: heredoc file not found", 1);
// 	while (1)
// 	{
// 		write(1, "<heredoc> ", 10); // print prompt
// 		str = get_next_line(0); // get line
// 		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0 //if str if NULL
// 			&& str[ft_strlen(limiter) + 1] == '\0') // or if the line is the limiter
// 			break ; // break the loop
// 		ft_putstr_fd(str, fd); // write the line in the file
// 		free(str); // free the line
// 	}
// 	close(fd); // close the file
// 	free(str); // free the line
// 	ft_exit(NULL, 3); // exit the child
// }

void	ft_heredoc(char *limiter, char *heredoc)
{
	char	*str;
	int		fd;
	pid_t	pid;

	pid = fork(); // make a child process
	if (pid == 0) // if i'm the child
	{
		fd = ft_open_fd(heredoc, 2); // open file
		if (fd == -1)
			ft_exit("Error: heredoc file not found", 1);
		while (1)
		{
			write(1, "<heredoc> ", 10); // print prompt
			str = get_next_line(0); // get line
			if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0 //if str if NULL
				&& str[ft_strlen(limiter) + 1] == '\0') // or if the line is the limiter
				break ; // break the loop
			ft_putstr_fd(str, fd); // write the line in the file
			free(str); // free the line
		}
		close(fd); // close the file
		free(str); // free the line
		ft_exit(NULL, 3); // exit the child
	}
	waitpid(pid, NULL, 0); // wait the child to finish de heredoc
}
