/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:48:32 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/03 13:10:50 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char **environ;

void	ft_mount_cmds(t_data *data);

char	*ft_trim_space(char *buffer)
{
	int		i;
	
	if (!buffer)
		return (buffer);
	i = ft_strlen(buffer) - 1;
	while (buffer[i] == ' ')
	{
		buffer[i] = '\0';
		i--;
	}
	while (*buffer == ' ')
		buffer++;
	return (buffer);
}

char	*ft_strtok(char *buffer, char sep)
{
	static char	*save;
	char *ret;
	
	if (!save)
		save = buffer;
	ret = save;
	while (save && *save == ' ')
		save++;
	while (save && *save != sep)
	{
		if (*save == '\0')
		{
			save = NULL;
			if (ft_is_only_space(ret))
				return (NULL);
			return (ret);
		}
		else if (*save == DBQUOTE || *save == SQUOTE)
		{
			save = strchr(save + 1, *save);
			if (!save)
				return (ret);
			save++;
		}
		else
			save++;
	}
	if (save)
		*save++ = '\0';
	return (ret);
}

int	ft_token_count(char *buffer, char sep)
{
	char *tmp;
	char *token;
	int i;
	
	i = 0;
	tmp = ft_strdup(buffer);
	token = ft_trim_space(ft_strtok(tmp, sep));
	while(token)
	{
		i++;
		token = ft_trim_space(ft_strtok(NULL, sep));
	}
	free(tmp);
	return (i);
}

void	ft_make_cmd_table(t_data *data)
{
	int i;

	i = 0;
	data->cmd_count = ft_token_count(data->buffer, '|');
	data->cmd = ft_calloc(sizeof(t_cmd), data->cmd_count + 1);
	if (data->cmd == NULL)
		ft_exit(data, "Malloc error\n", 2);
	data->cmd[0].buffer = ft_trim_space(ft_strtok(data->buffer, '|'));
	while (++i < data->cmd_count)
	{
		data->cmd[i].ct = 0;
		data->cmd[i].no_cmd = i;
		data->cmd[i].buffer = ft_trim_space(ft_strtok(NULL, '|'));
	}
}

void	ft_make_token(t_data *data)
{
	int c;
	int t;
	int count;

	c = -1;
	while (++c < data->cmd_count)
	{
		count = ft_token_count(data->cmd[c].buffer, ' ');
		data->cmd[c].token = ft_calloc(sizeof(char *), count + 1);
		t = 0;
		data->cmd[c].token[t] = ft_trim_space(ft_strtok(data->cmd[c].buffer, ' '));
		while (++t < count)
			data->cmd[c].token[t] = ft_trim_space(ft_strtok(NULL, ' '));
	}
}
