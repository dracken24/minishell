/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:23:33 by nadesjar          #+#    #+#             */
/*   Updated: 2022/05/07 00:05:13 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strcat(char *restrict dest, const char *restrict str)
{
	int	i;
	int	k;

	i = 0;
	while (dest[i] != '\0')
		i++;
	k = 0;
	while (str[k] != '\0')
		dest[i++] = str[k++];
	dest[i] = '\0';
	return (dest);
}
