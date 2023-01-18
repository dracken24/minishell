/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2023/01/17 11:40:31 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**g_env;
t_shell	shell;

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

void	ft_fd_env(char *name)
{
	int		fd;
	char	*path;

	path = ft_get_variable(name, 0);
	fd = ft_open_fd(path, 2);
	if (fd < 0)
		ft_exit(&shell, "error, open file hystory\n", -1);
	for (int i = 0; g_env[i]; i++)
	{
		ft_putstr_fd(g_env[i], fd);
		ft_putchar_fd('\n', fd);
	}
	close(fd);
}

void	ft_init_shell(t_shell *shell, char **env, int ac, char **av)
{
	(void)ac;
	(void)av;
	char	*tmp;
	char	*export;

	ft_memset(shell, 0, sizeof(t_shell));
	shell->expand[0] = 'a';
	shell->heredoc[0] = 'a';
	g_env = ft_remalloc(env, 2, 0);
	if (!g_env)
		ft_exit(shell, "Error: malloc failed\n", 1);
	ft_export_error(shell);
	
	tmp = getcwd(NULL, 0);
	export = ft_strjoin("STARTDIR=", tmp, 0);
	export = ft_strjoin(export, "/env", 1);
	ft_export(shell, export, 0);
	ft_free(export);
	export = ft_strjoin("HISTORY=", tmp, 0);
	export = ft_strjoin(export, "/history", 1);
	ft_export(shell, export, 0);
	ft_free(export);
	free(tmp);
	ft_add_history("HISTORY");
	ft_fd_env("STARTDIR");
}

int	main(int ac, char **av, char **env)
{
	char	*visiblePat;

	shell.history = 1;
	ft_init_shell(&shell, env, ac, av);
	while (1)
	{
		// ft_save_env("STARTDIR");
		ft_signal_on();
		visiblePat = mountPath();
		shell.buffer = readline(visiblePat);
		ft_save_history();
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
