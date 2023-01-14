/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:42:51 by nadesjar          #+#    #+#             */
/*   Updated: 2022/08/17 10:43:20 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char *str1, char const *str2, int f)
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
	if (f == 1)
		free(str1);
	return (tmp);
}
