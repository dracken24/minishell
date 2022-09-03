/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:04:49 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/03 14:10:33 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_print_dollard(char *buffer, t_data *data, int flag)
{
	char *str;

	str = ft_calloc(sizeof(char), ft_strlen(buffer));
	if (!str)
	{
		free(str);
		return (NULL);
	}
	data->i = 0;
	while (buffer[data->i] != '\0')
	{
		data->k = 0;
		while (buffer[data->i] != '$' && buffer[data->i] != '\0')
			printf("%c", buffer[data->i++]);
		if (buffer[data->i] == '\0')
			break ;
		data->k = -1;
		while (buffer[++data->i] != ' ' && buffer[data->i] != '\0')
			str[++data->k] = buffer[data->i];
		str = ft_get_variable(data, str);
		printf("%s", str);
	}
	if (flag == 0)
		printf("\n");
	return (NULL);
}

void	ft_echo(t_data *data, t_cmd *cmd, char *buffer)
{
	int flag;

	flag = 0;
	if (cmd->token[1][0] == '-' && cmd->token[1][1] == 'n')
		flag = 1;
	if (buffer[0] == '"')
	{
		buffer[ft_strlen(buffer) - 1] = '\0';
		buffer++;
	}
	if (ft_strchr_bool(buffer, '$') == true)
		buffer = ft_print_dollard(buffer, data, flag);
	else if (buffer && flag == 0)
		printf("%s\n", buffer);
	else
		printf("%s", buffer);
	cmd->ct = 1;
}

void	ft_env(t_data *data, t_cmd *cmd)
{
	int	i;

	i = -1;
	while(data->env[++i])
		printf("%s\n", data->env[i]);
	cmd->ct = 1;
}
