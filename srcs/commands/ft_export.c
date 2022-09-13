/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:20:35 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/13 14:33:56 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_data data;

void	ft_export_suite(char *arg, int nb)
{
	char	**temp;
	char	*duplicate;
	char	*var;
	int		i;

	duplicate = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	var = ft_get_variable(duplicate);
	if (var)
		ft_unset(duplicate, nb);
	free(duplicate);
	temp = ft_calloc(sizeof(char *), ft_array_size(data.env) + 2);
	if (temp == NULL)
		ft_exit("Malloc Error\n", 2);
	i = -1;
	while (data.env[++i])
		temp[i] = data.env[i];
	temp[i] = ft_strdup(arg);
	free(data.env);
	data.env = temp;
}

void	ft_export(char *arg, int nb)
{
	if (nb != 0)
		return ;
	if (ft_strchr(arg, '=') && arg[0] != '=')
		ft_export_suite(arg, nb);
	else if (arg == NULL)
		ft_env();
	ft_fd_env("STARTDIR");
}
