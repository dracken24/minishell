/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:43:29 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/05 12:24:40 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_table(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_count)
		free(data->cmd[i].token);
	free(data->cmd);
	free(data->buffer);
}

void	ft_exit(t_data *data, char *str, int s)
{
	if (s <= 0)
		ft_putstr_fd(str, 2);
	if (s <= 1)
		free(data->buffer);
	if (s <= 2)
		ft_free_ptr(data->env);
	if (s <= 3)
		ft_free_table(data);
	exit(0);
}
