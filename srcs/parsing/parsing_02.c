/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:48:32 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/03 12:58:28 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_open_fds_suite(t_data *data, int i, int k);

void	ft_print_table(t_data *data)
{
	int i;
	int j;
	
	printf("\n-- Print Table Start --\n\n");
	ft_color(3);
	printf("NBR DE CMDS: %d\n", data->cmd_count);
	i = 0;
	while (i < data->cmd_count)
	{
		printf("\nCMD #: %d\n", data->cmd[i].no_cmd + 1);
		printf("INFILE: %d\n", data->cmd[i].infile);
		printf("OUTFILE: %d\n", data->cmd[i].outfile);
		printf("BUFF: %s\n", data->cmd[i].buffer);
		j = 0;
		ft_color(2);
		while (data->cmd[i].token[j])
		{
			printf("TOKEN [%d]%s\n", j, data->cmd[i].token[j]);
			j++;
		}
		ft_color(3);
		printf("PATH: %s\n", data->cmd[i].path);
		i++;
	}
	ft_color(8);
	printf("\n-- Print Table end --\n\n");
}

void 	ft_parse(t_data *data)
{
	ft_make_cmd_table(data);
	ft_make_token(data);
	ft_open_fds(data);
	ft_print_table(data);
	ft_execute_table(data);
}

void	ft_open_fds(t_data *data)
{
	int	i;
	int	k;

	i = -1;
	while (++i < data->cmd_count)
	{
		data->cmd[i].nbr_token = ft_nbr_ptr(data->cmd[i].token) - 1;
		k = -1;
		while (data->cmd[i].token[++k])
		{
			if (ft_strncmp(data->cmd[i].token[k], ">>", 2) == 0)
				data->cmd[i].outfile = ft_open_fd(data->cmd[i].token[++k], 4);
			else if (ft_strncmp(data->cmd[i].token[k], ">", 1) == 0)
				data->cmd[i].outfile = ft_open_fd(data->cmd[i].token[++k], 2);
			if (ft_strncmp(data->cmd[i].token[k], "cat", 3) == 0)
				data->cmd[i].infile = ft_open_fd(data->cmd[i].token[1], 1);
			if (ft_strncmp(data->cmd[i].token[k], "grep", 4) == 0)
				data->cmd[i].infile = ft_open_fd(data->cmd[i].token[2], 1);
			ft_open_fds_suite(data, i, k);
		}
	}
}

void	ft_open_fds_suite(t_data *data, int i, int k)
{
	if (ft_strncmp(data->cmd[i].token[k], "wc", 2) == 0)
	{
		if (data->cmd[i].nbr_token == 2 || data->cmd[i].nbr_token == 4)
			data->cmd[i].infile = ft_open_fd(data->cmd[i].token[1], 1);
		else if (data->cmd[i].nbr_token == 3 || data->cmd[i].nbr_token == 5)
			data->cmd[i].infile = ft_open_fd(data->cmd[i].token[2], 1);
	}
}
