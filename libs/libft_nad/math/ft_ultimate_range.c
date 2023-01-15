/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 12:47:32 by nadesjar          #+#    #+#             */
/*   Updated: 2022/05/07 00:01:39 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_ultimate_range(int **range, int min, int max)
{
	int	i;

	*range = malloc(sizeof *(range) * (max - min));
	if (range == NULL)
		return (-1);
	if (max <= min)
	{
		*range = NULL;
		return (0);
	}
	i = 0;
	while (i < max - min)
	{
		(*range)[i] = min + i;
		i++;
	}
	return (i);
}
