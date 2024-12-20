/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:21:33 by dantremb          #+#    #+#             */
/*   Updated: 2023/01/15 15:26:50 by dracken24        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char	**g_env;

static void	ft_make_heredoc(char *limiter, char *heredoc)
{
	int		fd;
	char	*str;

	fd = ft_open_fd(heredoc, 2);
	str = readline("heredoc > ");
	while (str)
	{
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0)
		{
			break ;
		}
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
		ft_free(str);
		str = readline("heredoc > ");
	}
	ft_free(str);
	close(fd);
}

static char	*ft_exp_heredoc(t_shell *shell, char *heredoc)
{
	char	*temps;
	char	*expand;

	expand = ft_strjoin("<", shell->heredoc, 0);
	expand = ft_strjoin(expand, "=", 1);
	temps = ft_strjoin(expand, heredoc, 0);

	free(heredoc);
	ft_export(shell, temps, 0);
	free(temps);

	expand[ft_strlen(expand) - 1] = '\0';
	temps = ft_get_variable(expand, 0);
	free(expand);

	return (temps);
}

void	ft_parse_heredoc(t_shell *shell, char **token)
{
	int		i;
	char	*str;

	i = -1;
	while (token[++i])
	{
		if (ft_strncmp(token[i], "<<", 2) == 0)
		{
			if (token[i][2] == '\0')
			{
				str = ft_exp_heredoc(shell, ft_strjoin("<", shell->heredoc, 0));
				ft_make_heredoc(token[i + 1], str);
				token[i][1] = '\0';
				token[i + 1] = str;
			}
			else
			{
				str = ft_exp_heredoc(shell, ft_strjoin("<", shell->heredoc, 0));
				ft_make_heredoc(&token[i][2], str);
				token[i] = str;
			}
			shell->heredoc[0] = shell->heredoc[0] + 1;
		}
	}
}

void	ft_parse_token(t_shell *shell)
{
	int	c;
	int	t;

	c = -1;
	while (++c < shell->nb_cmd)
	{
		shell->cmd[c].nb_token = ft_token_count(shell->cmd[c].buffer, ' ');
		shell->cmd[c].token = ft_calloc(sizeof(char *),
			shell->cmd[c].nb_token + 1);

		if (!shell->cmd[c].token)
		{
			ft_exit(shell, "Error: malloc failed\n", 1);
		}

		t = 0;
		shell->cmd[c].token[t] = ft_strtok(shell->cmd[c].buffer, ' ');
		while (shell->cmd[c].token[t++])
		{
			shell->cmd[c].token[t] = ft_strtok(NULL, ' ');
		}

		shell->cmd[c].save = shell->cmd[c].token;
		shell->cmd[c].open_error = 0;
		ft_parse_heredoc(shell, shell->cmd[c].token);
	}
}

void	specialCmds(t_shell *shell)
{
	if (shell->buffer && strncmp(shell->buffer, "lsa", 3) == 0)
	{
		char *tmp = ft_calloc(sizeof(char), ft_strlen(shell->buffer) + 4);
		for (int i = 3; i < (int)ft_strlen(shell->buffer); i++)
		{
			tmp[i - 3] = shell->buffer[i];
		}
		
		ft_free(shell->buffer);
		shell->buffer = ft_strjoin("ls -la", tmp, 2);
	}
}

int	ft_parse(t_shell *shell)
{
	int		i;

	i = 0;
	if (ft_buffer_integrity(shell) == 0)
	{
		ft_export_error(shell);
		return (0);
	}

	specialCmds(shell);
	shell->nb_cmd = ft_token_count(shell->buffer, '|');
	shell->cmd = ft_calloc(sizeof(t_cmd), shell->nb_cmd);
	shell->pid = ft_calloc(sizeof(pid_t), shell->nb_cmd);

	if (shell->pid == NULL || shell->cmd == NULL)
	{
		ft_exit(shell, "Error: malloc failed\n", 1);
	}

	shell->cmd[0].buffer = ft_trim_token(ft_strtok(shell->buffer, '|'), ' ');
	while (++i < shell->nb_cmd)
	{
		shell->cmd[i].buffer = ft_trim_token(ft_strtok(NULL, '|'), ' ');
	}

	ft_parse_token(shell);

	return (1);
}
