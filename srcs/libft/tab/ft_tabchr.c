/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:52:00 by nadesjar          #+#    #+#             */
/*   Updated: 2022/08/29 12:09:13 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

bool	ft_tabchr(char **tab, char *find)
{
	int i;
	int k;
	if (!tab || !find)
		return (false);
	i = -1;
	while (tab[++i])
	{
		k = -1;
		while (find[++k])
		{
			if (ft_strchr_bool(tab[i], find[k]))
				return (true);
		}
	}
	return (false);
}
