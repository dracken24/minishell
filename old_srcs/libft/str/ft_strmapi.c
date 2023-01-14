/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:11:58 by marvin            #+#    #+#             */
/*   Updated: 2022/05/07 00:06:06 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(const char *str, char (*f)(unsigned int, char))
{
	char	*temp;
	size_t	i;

	if (!str)
		return (NULL);
	temp = ft_strdup((char *) str);
	if (!temp)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		temp[i] = f(i, str[i]);
		i++;
	}
	return (temp);
}
