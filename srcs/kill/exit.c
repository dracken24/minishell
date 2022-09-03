/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:43:29 by nadesjar          #+#    #+#             */
/*   Updated: 2022/08/31 09:50:03 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char **environ;

void	ft_exit(t_data *data, char *str, int s)
{
	ft_free_pars(data);
	if (s <= 0)
		ft_putstr_fd(str, 2);
	if (s <= 1)
		free(data->buffer);
	if (s <= 2)
		ft_free_ptr(data->env);
	if (s <= 3)
		free(data->cmd);
	exit(0);
}
