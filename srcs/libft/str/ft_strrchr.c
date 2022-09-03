/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:47:16 by nadesjar          #+#    #+#             */
/*   Updated: 2022/05/07 00:05:56 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	len;
	char	*str2;

	str2 = (char *)str;
	len = (size_t)ft_strlen((char *)str);
	if (c == '\0')
	{
		while (len > 0)
		{
			str2++;
			len--;
		}
		return (str2);
	}
	while (len > 0)
	{
		if ((char)str2[len] == (char)c)
			return (&str2[len]);
		len--;
	}
	if ((char)str[0] == (char)c)
		return ((char *)str);
	return (NULL);
}
