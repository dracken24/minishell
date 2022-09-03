/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 12:23:51 by nadesjar          #+#    #+#             */
/*   Updated: 2022/05/07 00:05:50 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *src, unsigned int start, size_t len)
{
	char	*str;
	size_t	my_len;
	size_t	i;

	if (!src)
		return (NULL);
	my_len = ft_strlen((char *) src);
	if (my_len < len)
		str = ft_calloc((my_len + 1), sizeof(char));
	else
		str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (start >= my_len)
		return (str);
	i = 0;
	while (i < len && src[i] != '\0')
	{
		str[i] = src[start + i];
		i++;
	}
	return (str);
}
