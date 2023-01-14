/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 11:43:29 by nadesjar          #+#    #+#             */
/*   Updated: 2022/05/07 00:04:40 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	size_t	i;

	if (!src && !dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		((char *) dest)[i] = ((char *) src)[i];
		i++;
	}
	return ((char *) dest);
}
