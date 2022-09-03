/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:34:41 by nadesjar          #+#    #+#             */
/*   Updated: 2022/05/07 00:05:07 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(char *src)
{
	char	*cpstr;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(src);
	cpstr = malloc(sizeof(char) * (len + 1));
	if (!cpstr)
		return (NULL);
	while (src[i] != '\0')
	{
		cpstr[i] = src[i];
		i++;
	}
	cpstr[i] = '\0';
	return (cpstr);
}
