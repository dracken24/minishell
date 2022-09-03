/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_bool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:13:40 by nadesjar          #+#    #+#             */
/*   Updated: 2022/07/28 16:16:59 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

bool	ft_strchr_bool(const char *str, int c)
{
	size_t	len;

	len = ft_strlen((char *)str);
	if (c == '\0')
	{
		while (len > 0)
		{
			str++;
			len--;
		}
		return (false);
	}
	while (*str)
	{
		if (*str == (char)c)
			return (true);
		str++;
	}
	return (false);
}
