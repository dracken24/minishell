/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:26:31 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/11 20:21:51 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(char *str1, char *str2, size_t n)
{
	size_t	i;

	i = -1;
	if (n == 0)
		return (0);
	while ((str1[++i] && str2[i]) && (str1[i] == str2[i]) && (i < n - 1))
		;
	return ((unsigned char) str1[i] - (unsigned char) str2[i]);
}
