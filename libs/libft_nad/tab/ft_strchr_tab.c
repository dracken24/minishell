/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:26:31 by nadeskar          #+#    #+#             */
/*   Updated: 2022/12/13 23:48:42 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr_tab(char **tab, char **tab_2, size_t nbr_turn)
{
	size_t	i;
	size_t	k;

	i = -1;
	while (tab[++i] && i < nbr_turn)
	{
		k = -1;
		while (tab_2[++k])
		{
			if (ft_strncmp(tab[i], tab_2[k], ft_strlen(tab[i])) == 0)
				return (tab[i]);
		}
	}
	return (NULL);
}
