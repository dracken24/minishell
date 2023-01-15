/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:47:16 by nadesjar          #+#    #+#             */
/*   Updated: 2022/10/21 12:29:34 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *str, int c, size_t len)
{
	size_t	len2;
	char	*str2;

	str2 = (char *)str;
	len2 = (size_t)ft_strlen((char *)str);
	if (c == '\0')
	{
		while (len2 > 0)
		{
			str2++;
			len2--;
		}
		return (str2);
	}
	while (len2 > 0 && len > 0)
	{
		if ((char)str2[len2] == (char)c)
			return (&str2[len2]);
		len--;
		len2--;
	}
	if ((char)str[0] == (char)c)
		return ((char *)str);
	return (NULL);
}
