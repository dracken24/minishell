/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr_sign_in_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:38:42 by nadesjar          #+#    #+#             */
/*   Updated: 2022/08/29 12:48:01 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_nbr_sign_in_tab(char **tab, char c)
{
	int	i;
	int	k;
	int	ret;
	
	if (!tab || !c)
		return (-1);
	ret = 0;
	i = -1;
	while (tab[++i])
	{
		k = -1;
		while (tab[i][++k])
		{
			if (tab[i][k] == c)
				ret += 1;
		}
	}
	return (ret);
}
