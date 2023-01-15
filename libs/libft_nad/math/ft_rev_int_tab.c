/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_int_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 10:37:18 by nadesjar          #+#    #+#             */
/*   Updated: 2022/05/07 00:04:04 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_rev_int_tab(int *tab, int size)
{
	int	temp;
	int	x;

	x = 0;
	size--;
	while (x < size)
	{
		temp = tab[size];
		tab[size] = tab[x];
		tab[x] = temp;
		x++;
		size--;
	}
}
