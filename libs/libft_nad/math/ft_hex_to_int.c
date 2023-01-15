/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_to_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:15:30 by nadesjar          #+#    #+#             */
/*   Updated: 2022/12/13 23:31:11 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_hex_to_int(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

int	ft_str_to_hexa(const char *str)
{
	int	hexa;
	int	i;

	hexa = 0;
	i = 0;
	while (str[i] != '\0')
	{
		hexa = hexa * 16 + ft_hex_to_int(str[i]);
		i++;
	}
	return (hexa);
}
