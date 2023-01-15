/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr_ret_tofind.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:41:08 by nadesjar          #+#    #+#             */
/*   Updated: 2022/12/13 23:34:20 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr_ret_tofind(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	k;

	i = 0;
	if (to_find[i] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i < len)
	{
		k = 0;
		while (str[i + k] == to_find[k] && i + k < len)
		{
			if (to_find[k + 1] == '\0')
				return ((char *)to_find);
			k++;
		}
		i++;
	}
	return (0);
}
