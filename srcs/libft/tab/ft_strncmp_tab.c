/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:26:31 by nadesjar          #+#    #+#             */
/*   Updated: 2022/08/29 14:36:59 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp_tab(char **tab, char *str, size_t len, size_t nbr_turn)
{
	size_t	i;
	size_t	j;

	if (len == 0)
		return (0);
	i = -1;
	while (tab[++i] && i < nbr_turn)
	{
		if (!tab[i])
			break ;
		j = 0;
		while ((tab[i][j] && str[j]) && (tab[i][j] == str[j]) && (j < len))
		{
			if (j == len - 1)
				return ((unsigned char)tab[i][j] - (unsigned char)str[j]);
			j++;
		}
	}
	return (-1);
}
