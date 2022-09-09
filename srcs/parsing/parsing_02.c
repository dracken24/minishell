/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:48:32 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/08 15:09:24 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_trim_token(char *buffer, char sep)
{
	int		i;
	if (!buffer)
		return (buffer);
	i = ft_strlen(buffer) - 1;
	while (buffer[i] == sep)
	{
		buffer[i] = '\0';
		i--;
	}
	while (*buffer == sep)
		buffer++;
	return (buffer);
}

int	ft_token_count(char *buffer, char sep)
{
	char *tmp;
	char *token;
	int i;
	
	i = 0;
	tmp = ft_strdup(buffer);
	token = ft_trim_token(ft_strtok(tmp, sep), ' ');
	while(token)
	{
		i++;
		token = ft_trim_token(ft_strtok(NULL, sep), ' ');
	}
	free(tmp);
	return (i);
}

char	*ft_remove_char(char *token, char sep)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == sep)
		{
			j = i;
			while (token[j])
			{
				token[j] = token[j + 1];
				j++;
			}
		}
		else
			i++;
	}
	return (token);
}

char	*ft_expand(t_data *data, char *token, int flag)
{
	char	*temp[4];

	temp[0] = ft_strchr(token, '$');
	temp[1] = ft_remove_char(ft_substr(token, 0, temp[0] - token), '\"');
	temp[2] = temp[0] + 1;
	while (++temp[0])
		if (*temp[0] == '\0' || *temp[0] == ' ' || *temp[0] == '$' || *temp[0] == '"' || *temp[0] == '\'')
			break ;
	temp[2] = ft_substr(temp[2] , 0, temp[0] - temp[2] );
	temp[3] = ft_get_variable(data, temp[2] );
	temp[3]  = ft_strjoin(temp[1], temp[3], 1);
	free (temp[2]);
	temp[1] = ft_remove_char(ft_substr(temp[0], 0, ft_strlen(temp[0])), '\"');
	temp[0] = ft_strjoin(temp[3] , temp[1], 1);
	free(temp[1]);
	if (flag == 1)
		free (token);
	if (ft_strchr(temp[0], '$'))
		temp[0] = ft_expand(data, temp[0], 1);
	return (temp[0]);
}

// void	ft_clean_token(t_data *data, char **token)
// {
// 	int	t;

// 	t = 0;
// 	while (token[t])
// 	{
// 		if (token[t][0] == '\'' && token[t][ft_strlen(token[t]) - 1] == '\'')
// 			ft_remove_char(token[t], '\'');
// 		else if (token[t][0] == '\"'
// 			&& token[t][ft_strlen(token[t]) - 1] == '\"')
// 		{
// 			if (ft_strchr(token[t], '$'))
// 				token[t] = ft_expand_variable(data, token[t]);
// 			else
// 				ft_remove_char(token[t], '\"');
// 		}
// 		else
// 		{
// 			token[t] = ft_trim_token(token[t], ' ');
// 			if (ft_strchr(token[t], '$'))
// 				token[t] = ft_expand_variable(data, token[t]);
// 		}
// 		t++;
// 	}
// }

// void	ft_make_token(t_data *data)
// {
// 	int	c;
// 	int	t;
// 	int	count;

// 	c = -1;
// 	while (++c < data->cmd_count)
// 	{
// 		count = ft_token_count(data->cmd[c].buffer, ' ');
// 		data->cmd[c].token = ft_calloc(sizeof(char *), count + 2);
// 		t = 0;
// 		data->cmd[c].token[t] = ft_strtok(data->cmd[c].buffer, ' ');
// 		while (data->cmd[c].token[t])
// 		{
// 			t++;
// 			data->cmd[c].token[t] = ft_strtok(NULL, ' ');
// 		}
// 	}
// 	c = -1;
// 	while (++c < data->cmd_count)
// 		ft_clean_token(data, data->cmd[c].token);
// }

// void	ft_parse(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	data->cmd_count = ft_token_count(data->buffer, '|');
// 	data->cmd = ft_calloc(sizeof(t_cmd), data->cmd_count + 1);
// 	if (data->cmd == NULL)
// 		ft_exit(data, "Malloc error\n", 2);
// 	data->cmd[0].buffer = ft_trim_token(ft_strtok(data->buffer, '|'), ' ');
// 	while (++i < data->cmd_count)
// 		data->cmd[i].buffer = ft_trim_token(ft_strtok(NULL, '|'), ' ');
// 	ft_make_token(data);
// }
