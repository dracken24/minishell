/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:44:29 by nadesjar          #+#    #+#             */
/*   Updated: 2022/05/07 00:06:14 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	k;
	size_t	len;
	size_t	dest_len;

	i = 0;
	len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	k = dest_len;
	if (dest_len < size - 1 && size > 0)
	{
		while (src[i] && dest_len + i < size - 1)
		{
			dest[k] = src[i];
			k++;
			i++;
		}
		dest[k] = 0;
	}
	if (dest_len >= size)
		dest_len = size;
	return (dest_len + len);
}
