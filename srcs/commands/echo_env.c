/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 12:04:49 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/07 18:57:14 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **arg)
{
	int i;
	int flag;

	flag = 0;
	i = 1;
	if (arg[1] && ft_strncmp(arg[1], "-n\0", 3) == 0)
	{
		flag = 1;
		i++;
	}
	while (arg[i])
	{
		if (ft_is_only(arg[i], ' '))
			i++;
		else
		{
		printf("%s", arg[i++]);
		if (arg[i])
			printf(" ");
		}
	}
	if (flag == 0)
		printf("\n");
}

void	ft_env(t_data *data)
{
	int i;

	i = -1;
	while(data->env[++i])
		printf("%s\n", data->env[i]);
}

/** Manque '' a gerer **/
// void	ft_print_dollard(char *buffer, t_data *data, int flag)
// {
// 	data->i = 0;
// 	while (buffer[data->i] != '\0')
// 	{
// 		data->str = ft_calloc(sizeof(char), BUFFER_SIZE);
// 		if (!data->str)
// 		{
// 			free(data->str);
// 			return ;
// 		}
// 		data->str[0] = '\0';
// 		data->k = 0;
// 		while (buffer[data->i] != '$' && buffer[data->i] != '\0')
// 			printf("%c", buffer[data->i++]);
// 		if (buffer[data->i] == '\0')
// 			break ;
// 		data->k = -1;
// 		while (buffer[++data->i] != ' ' && buffer[data->i] != '\0')
// 			data->str[++data->k] = buffer[data->i];
// 		data->str = ft_get_variable(data, data->str);
// 		printf("%s", data->str);
// 		// free(data->str);
// 	}
// 	if (flag == 0)
// 		printf("\n");
// }

// void	ft_echo(t_data *data, t_cmd *cmd, char *buffer)
// {
// 	int flag;

// 	flag = 0;
// 	if (cmd->token[1][0] == '-' && cmd->token[1][1] == 'n')
// 		flag = 1;
// 	if (buffer[0] == '"')
// 	{
// 		buffer[ft_strlen(buffer) - 1] = '\0';
// 		buffer++;
// 	}
// 	ft_print_dollard(buffer, data, flag);
// 	cmd->ct = 1;
// }

// void	ft_env(t_data *data, t_cmd *cmd)
// {
// 	int	i;

// 	i = -1;
// 	while(data->env[++i])
// 		printf("%s\n", data->env[i]);
// 	cmd->ct = 1;
// }
