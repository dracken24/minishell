/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 14:10:07 by nadesjar          #+#    #+#             */
/*   Updated: 2022/05/07 00:04:07 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	*ft_range(int min, int max)
{
	int	*diff;
	int	i;

	if (min >= max)
		return (NULL);
	diff = malloc(sizeof(int) * (max - min));
	i = 0;
	while (i < (max - min))
	{
		diff[i] = min + i;
		i++;
	}
	return (diff);
}
