/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_pos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:37:20 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/26 12:21:16 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

long int	ft_atol_pos(const char *str)
{
	int			i;
	int long	numb;

	i = 0;
	numb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		return(-3);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		numb = (str[i++] - '0') + (numb * 10);
		if (numb < MININT || numb > MAXINT)
			return (2147483648);
		else if (!(str[i] >= '0' && str[i] <= '9'))
			return (numb);
	}
	return (0);
}
