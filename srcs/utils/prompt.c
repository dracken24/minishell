/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:55:19 by dracken24         #+#    #+#             */
/*   Updated: 2023/01/18 10:42:16 by dracken24        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <dirent.h> 

extern char	**g_env;
extern t_shell	shell;

char*	mountPath(void)
{
	char	*tmp;
	char	*tmp2;
	char	*head = NULL;
	char	*ret;
	int		fd;
	DIR		*dir;

	tmp = getcwd(NULL, 0);

	ret = ft_strjoin("\x1b[33m", "-----------------------------------------------------------------------------\n", 0);
	ret = ft_strjoin(ret, "\x1b[34m", 1);
	ret = ft_strjoin(ret, "CWD: ", 1);
	ret = ft_strjoin(ret, tmp, 1);
	ret = ft_strjoin(ret, "/ -->  branch:  ", 1);
	
	// check if dir .git exist. if yes, head = good line
	dir = opendir(".git");
	if (dir != NULL)
	{
		chdir(".git");
		if ((fd = open("HEAD", O_RDONLY)) == -1) // branch is in HEAD file ex: "ref: refs/heads/main"
			ft_exit(&shell, "error, open file HEAD\n", -1);
		if (fd)
		{
			head = get_next_line(fd);
			while (head && strncmp(head, "ref:", 4) != 0)
			{
				ft_free(head);
				head = get_next_line(fd);
			}
		}
		if (fd)
			close(fd);
		chdir("..");

		// take name of branch if dir exist, else print none in red
		fd = ft_strlen(head);
		while (head[fd] != '/')
			fd--;
		tmp2 = strdup(&head[fd + 1]);
		ret = ft_strjoin(ret , "\x1b[36m", 1);
		ret = ft_strjoin(ret, tmp2, 1);
		ret = ft_strjoin(ret , "\x1b[33m", 1);
		ft_free(tmp2);
		ft_free(head);
		closedir(dir);
	}
	else
	{
		ret = ft_strjoin(ret , "\x1b[31m", 1);
		ret = ft_strjoin(ret, "none\n", 1);
		ret = ft_strjoin(ret , "\x1b[33m", 1);
	}
	
	ret = ft_strjoin(ret, "-----------------------------------------------------------------------------\n", 1);
	ret = ft_strjoin(ret , "\x1b[36m", 1);
	ret = ft_strjoin(ret, "DrackenShell : ", 1);
	ret = ft_strjoin(ret, "\e[0;35m", 1);

	ft_free(tmp);
	return (ret);
}
