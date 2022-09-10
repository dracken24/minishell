/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:48:32 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/10 10:54:05 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_data data;

char	*ft_expand_variable(char *token)
{
	char	*temps;
	char	*expand;

	if (token[0] == '$' && ft_strchr(&token[1], '$') == NULL)
		token = ft_get_variable(&token[1]);
	else
	{
		if (token[0] == '\"')
			token = ft_expand(token + 1, 0);
		else
			token = ft_expand(token, 0);
		expand = ft_strjoin(data.expand, "-expand=", 0);
		temps = ft_strjoin(expand, token, 0);
		free(token);
		ft_export(temps);
		free(temps);
		expand[ft_strlen(expand) - 1] = '\0';
		token = ft_get_variable(expand);
		free(expand);
		data.expand[0] = data.expand[0] + 1; 
	}
	return (token);
}

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

char	*ft_expand_heredoc(char *heredoc)
{
	char	*temps;
	char	*expand;

	expand = ft_strjoin(data.heredoc, "heredoc=", 0);
	temps = ft_strjoin(expand, heredoc, 0);
	free(heredoc);
	ft_export(temps);
	free(temps);
	expand[ft_strlen(expand) - 1] = '\0';
	heredoc = ft_get_variable(expand);
	free(expand);
	data.heredoc[0] = data.heredoc[0] + 1; 

	return (heredoc);
}

void	ft_check_redirect(char **token)
{
	int i;
	char	*str;

	i = -1;
	while (token[++i])
	{
		if (ft_strncmp(token[i], "<<\0", 3) == 0)
		{
			str = ft_expand_heredoc(ft_strjoin(&data.heredoc[0], "heredoc", 0));
			ft_heredoc(token[i + 1], str);
			token[i][1] = '\0';
			token[i + 1] = str;
		}
		else if (ft_strncmp(token[i], "<<", 2) == 0)
		{
			
			return;
		}
	}
}

void	ft_make_token(void)
{
	int c;
	int t;
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
		ft_check_redirect(data.cmd[c].token);
	// c = -1;
	// while (++c < data.cmd_count)
	// {
	// 	ft_find_redirect(data, c);
	// 	ft_clean_token(data, data.cmd[c].token);
	// }
}

void 	ft_parse(void)
{
	int i;

	i = 0;
	data.cmd_count = ft_token_count(data.buffer, '|');
	data.cmd = ft_calloc(sizeof(t_cmd), data.cmd_count + 1);
	data.pid = ft_calloc(sizeof(pid_t), data.cmd_count - 1);
	printf("NBR CMD: %d\n", data.cmd_count);
	if (data.cmd == NULL || data.pid == NULL)
		ft_exit("Malloc error\n", 2);
	data.cmd[0].buffer = ft_trim_token(ft_strtok(data.buffer, '|'), ' ');
	while (++i < data.cmd_count)
		data.cmd[i].buffer = ft_trim_token(ft_strtok(NULL, '|'), ' ');
	ft_make_token();
}
