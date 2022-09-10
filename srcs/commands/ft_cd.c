/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:40:45 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/10 10:22:14 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern t_data data;

void	ft_cd(char *buffer)
{
	int	new;
	int	old;
	int	ret;

	ret = chdir(buffer);
	old = -1;
	while (data.env[++old])
	{
		if (ft_strncmp(data.env[old], "OLDPWD=", 7) == 0)
			break ;
	}
	new = -1;
	while (data.env[++new])
	{
		if (ft_strncmp(data.env[new], "PWD=", 4) == 0)
			break ;
	}
	if (ret == 0)
	{
		free (data.env[old]);
		data.env[old] = data.env[new];
		data.env[new] = ft_strjoin("PWD=", getcwd(NULL, 0), 0);
	}
}
