/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:48:32 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/05 15:49:47 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_clean_token(t_data *data, char **token)
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
				token[t] = ft_expand_variable(data, token[t]);
			else
				ft_remove_char(token[t], '\"');
		}
		else
		{
			token[t] = ft_trim_token(token[t], ' ');
			if (ft_strchr(token[t], '$'))
				token[t] = ft_expand_variable(data, token[t]);
		}
		t++;
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
		data->cmd[c].token = ft_calloc(sizeof(char *), count + 2);
		t = 0;
		data->cmd[c].token[t] = ft_strtok(data->cmd[c].buffer, ' ');
		while (data->cmd[c].token[t])
		{
			t++;
			data->cmd[c].token[t] = ft_strtok(NULL, ' ');
		}
	}
	c = -1;
	while (++c < data->cmd_count)
		ft_clean_token(data, data->cmd[c].token);
}

void 	ft_parse(t_data *data)
{
	int i;

	i = 0;
	data->cmd_count = ft_token_count(data->buffer, '|');
	data->cmd = ft_calloc(sizeof(t_cmd), data->cmd_count + 1);
	if (data->cmd == NULL)
		ft_exit(data, "Malloc error\n", 2);
	data->cmd[0].buffer = ft_trim_token(ft_strtok(data->buffer, '|'), ' ');
	while (++i < data->cmd_count)
		data->cmd[i].buffer = ft_trim_token(ft_strtok(NULL, '|'), ' ');
	ft_make_token(data);
}

// void	ft_open_fds_suite(t_data *data, int i, int k);

// void	ft_print_table(t_data *data)
// {
// 	int i;
// 	int j;
	
// 	printf("\n-- Print Table Start --\n\n");
// 	ft_color(3);
// 	printf("NBR DE CMDS: %d\n", data->cmd_count);
// 	i = 0;
// 	while (i < data->cmd_count)
// 	{
// 		printf("\nCMD #: %d\n", data->cmd[i].no_cmd + 1);
// 		printf("INFILE: %d\n", data->cmd[i].infile);
// 		printf("OUTFILE: %d\n", data->cmd[i].outfile);
// 		printf("BUFF: %s\n", data->cmd[i].buffer);
// 		j = 0;
// 		ft_color(2);
// 		while (data->cmd[i].token[j])
// 		{
// 			printf("TOKEN [%d]%s\n", j, data->cmd[i].token[j]);
// 			j++;
// 		}
// 		ft_color(3);
// 		printf("PATH: %s\n", data->cmd[i].path);
// 		i++;
// 	}
// 	ft_color(8);
// 	printf("\n-- Print Table end --\n\n");
// }

// void 	ft_parse(t_data *data)
// {
// 	ft_make_cmd_table(data);
// 	ft_make_token(data);
// 	ft_open_fds(data);
// 	ft_print_table(data);
// 	ft_execute_table(data);
// }
