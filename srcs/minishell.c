/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2023/01/13 21:11:45 by dracken24        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <dirent.h> 

char	**g_env;

void	ft_parse_export(t_shell *shell, int nb)
{
	int	i;

	if (shell->cmd[nb].nb_token == 1)
		ft_env(0);
	else
	{
		i = 0;
		while (++i < shell->cmd[nb].nb_token)
			ft_export(shell, shell->cmd[nb].token[i], 1);
	}
}

void	ft_parse_unset(t_shell *shell, int nb)
{
	int	i;

	i = 0;
	while (++i < shell->cmd[nb].nb_token)
		ft_unset(shell->cmd[nb].token[i]);
}

void	ft_exit(t_shell *shell, char *msg, int errno)
{
	ft_putstr_fd(msg, 2);
	ft_clear_command(shell);
	g_env = (char **)ft_free_array(g_env);
	rl_clear_history();
	exit(errno);
}

void	ft_init_shell(t_shell *shell, char **env, int ac, char **av)
{
	(void)ac;
	(void)av;
	ft_memset(shell, 0, sizeof(t_shell));
	shell->expand[0] = 'a';
	shell->heredoc[0] = 'a';
	g_env = ft_remalloc(env, 0, 0);
	if (!g_env)
		ft_exit(shell, "Error: malloc failed\n", 1);
	ft_export_error(shell);
}

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
	// ret = ft_strjoin(ret, "| ", 1);
	ret = ft_strjoin(ret, "\x1b[34m", 1);
	ret = ft_strjoin(ret, "CWD: ", 1);
	ret = ft_strjoin(ret, tmp, 1);
	ret = ft_strjoin(ret, "/ -->  branch:  ", 1);
	
	// check if dir .git exist. if yes, head = good line
	dir = opendir(".git");
	if (dir != NULL)
	{
		chdir(".git");
		fd = open("HEAD", O_RDONLY); // branch is in HEAD file ex: "ref: refs/heads/main"
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
	ret = ft_strjoin(ret, "DrackenShell: ", 1);
	ret = ft_strjoin(ret, "\e[0;35m", 1);

	ft_free(tmp);
	return (ret);
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;
	char	*visiblePat;

	ft_init_shell(&shell, env, ac, av);
	while (1)
	{
		ft_signal_on();
		visiblePat = mountPath();
		shell.buffer = readline(visiblePat);
		if (ft_parse(&shell) == 1)
		{
			ft_signal_off();
			ft_execute_cmd(&shell, 0);
		}
		ft_free(visiblePat);
		ft_clear_command(&shell);
		printf("\n");
	}
	return (0);
}
