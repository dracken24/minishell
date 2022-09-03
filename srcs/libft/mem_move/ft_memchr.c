/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:49:24 by nadesjar          #+#    #+#             */
/*   Updated: 2022/05/07 00:04:45 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *src, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (((unsigned char *) src)[i] == (unsigned char) c)
			return (&((void *) src)[i]);
		i++;
	}
	return (NULL);
}
