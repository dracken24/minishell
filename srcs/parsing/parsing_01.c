/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:48:32 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/11 17:19:30 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_data data;

void	ft_clean_token(char **token)
{
	int t;

	t = 0;
	while (token[t])
	{
		if (token[t][0] == '\'' && token[t][ft_strlen(token[t]) - 1] == '\'')
			ft_remove_char(token[t], '\'');
		else if (token[t][0] == '\"' && token[t][ft_strlen(token[t]) - 1] == '\"')
		{
			if (ft_strchr(token[t], '$'))
				token[t] = ft_expand_variable(token[t]);
			else
				ft_remove_char(token[t], '\"');
		}
		else
		{
			token[t] = ft_trim_token(token[t], ' ');
			if (ft_strchr(token[t], '$'))
				token[t] = ft_expand_variable(token[t]);
		}
		t++;
	}
}

// char	*ft_expand_heredoc(char *heredoc)
// {
// 	char	*temps;
// 	char	*expand;

// 	expand = ft_strjoin("<", &data.heredoc, 0);
// 	expand = ft_strjoin(expand, "=", 1);
// 	temps = ft_strjoin(expand, heredoc, 0);
// 	free(heredoc);
// 	ft_export(temps, 1);
// 	free(temps);
// 	expand[ft_strlen(expand) - 1] = '\0';
// 	heredoc = ft_get_variable(expand);
// 	free(expand);
// 	data.heredoc = data.heredoc + 1;
// 	return (heredoc);
// }

char	*ft_expand_heredoc(char *heredoc)
{
	char	*temps;
	char	*expend;

	expend = ft_strjoin(&data.heredoc, "heredoc=", 0);
	temps = ft_strjoin(expend, heredoc, 0);
	free(heredoc);
	ft_export(temps, 0);
	free(temps);
	expend[ft_strlen(expend) - 1] = '\0';
	heredoc = ft_get_variable(expend);
	free(expend);
	data.heredoc = data.heredoc + 1; 

	return (heredoc);
}

int	ft_check_redirect(char **token)
{
	int 	i;
	char	*str;

	i = -1;
	while (token[++i])
	{
		if (ft_strncmp(token[i], "<<\0", 3) == 0)
		{
			str = ft_expand_heredoc(ft_strjoin(&data.heredoc, "heredoc", 0));
			ft_heredoc(token[i + 1], str);
			token[i][1] = '\0';
			token[i + 1] = str;
		}
		else if (ft_strncmp(token[i], "<<", 2) == 0)
		{
			
			return 0;
		}
	}
	return (0);
}

int	ft_make_token(void)
{
	int c;
	int t;
	// int	ret;
	int count;

	c = -1;
	while (++c < data.cmd_count)
	{
		count = ft_token_count(data.cmd[c].buffer, ' ');
		data.cmd[c].token = ft_calloc(sizeof(char *), count + 2);
		t = 0;
		data.cmd[c].token[t] = ft_strtok(data.cmd[c].buffer, ' ');
		while (data.cmd[c].token[t])
		{
			t++;
			data.cmd[c].token[t] = ft_strtok(NULL, ' ');
		}
	}
	c = -1;
	while (++c < data.cmd_count)
	{
		ft_check_redirect(data.cmd[c].token);
	}
	return (0);
}

int	ft_parse(void)
{
	int i;

	i = 0;
	data.cmd_count = ft_token_count(data.buffer, '|');
	data.cmd = ft_calloc(sizeof(t_cmd), data.cmd_count + 1);
	data.pid = ft_calloc(sizeof(pid_t), data.cmd_count - 1);
	if (data.cmd == NULL || data.pid == NULL)
		ft_exit("Malloc error\n", 2);
	data.cmd[0].buffer = ft_trim_token(ft_strtok(data.buffer, '|'), ' ');
	while (++i < data.cmd_count)
		data.cmd[i].buffer = ft_trim_token(ft_strtok(NULL, '|'), ' ');
	ft_make_token();
	return (0);
}
