/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 20:44:21 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/11 18:55:10 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_data data;

char	*ft_get_path(int nb)
{
	char	*program;
	char	*env_path;
	char	**fcnt_path;
	char	*test_path;
	int		i;

	i = -1;
	if (access(data.cmd[nb].token[0], F_OK | X_OK) == 0)
		return (data.cmd[nb].token[0]);
	program = ft_strjoin("/", data.cmd[nb].token[0], 0);
	env_path = ft_get_variable("PATH");
	fcnt_path = ft_split(env_path, ':');
	if (program == NULL || env_path == NULL || fcnt_path == NULL)
		return (NULL);
	while (fcnt_path[++i])
	{
		test_path = ft_strjoin(fcnt_path[i], program, 0);
		if (access(test_path, F_OK | X_OK) == 0)
			break ;
		free (test_path);
		test_path = NULL;
	}
	ft_free_ptr(fcnt_path);
	free(program);
	return (test_path);
}
