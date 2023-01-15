/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:52:51 by nadesjar          #+#    #+#             */
/*   Updated: 2022/05/07 00:04:10 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_print_nbr(int nbr)
{
	int	x;

	x = 0;
	if (nbr > 9)
		ft_print_nbr(nbr / 10);
	x = nbr % 10 + '0';
	ft_putchar_fd(x, 1);
}

void	ft_putnbr(int nb)
{
	if (nb == 0)
		ft_putchar_fd('0', 1);
	else if (nb != -2147483648)
	{
		if (nb < 0)
		{
			ft_putchar_fd('-', 1);
			nb = nb * -1;
		}
		if (nb)
			ft_print_nbr(nb);
	}
	else if (nb == -2147483648)
		write(1, "-2147483648", 11);
}
