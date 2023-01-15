/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:42:51 by nadesjar          #+#    #+#             */
/*   Updated: 2022/12/13 23:34:00 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_free_str(char *str1, char *str2, int nbr)
{
	if (nbr == 1)
		free(str1);
	if (nbr == 2)
		free(str2);
	if (nbr == 3)
	{
		free(str1);
		free(str2);
	}
}

char	*ft_strjoin(char *str1, char *str2, int nbr)
{
	char	*tmp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (!str1 || !str2)
		return (NULL);
	tmp = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (tmp == NULL)
		return (NULL);
	while (str1 && str1[i])
	{
		tmp[i] = str1[i];
		i++;
	}
	while (str2 && str2[k])
		tmp[i++] = str2[k++];
	tmp[i] = '\0';
	ft_free_str(str1, str2, nbr);
	return (tmp);
}
