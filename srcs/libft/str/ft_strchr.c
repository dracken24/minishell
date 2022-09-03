/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:53:39 by nadesjar          #+#    #+#             */
/*   Updated: 2022/05/07 00:05:10 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	len;

	len = ft_strlen((char *)str);
	if (c == '\0')
	{
		while (len > 0)
		{
			str++;
			len--;
		}
		return ((char *)str);
	}
	while (*str)
	{
		if (*str == (char)c)
		{
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}
