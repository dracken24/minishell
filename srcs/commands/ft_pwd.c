/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:37:17 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/03 13:13:36 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_pwd(t_data *data, t_cmd *cmd)
{
	printf("%s\n", ft_get_variable(data, "PWD"));
	cmd->ct = 1;
	return (true);
}
