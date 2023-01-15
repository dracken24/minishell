/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:52:51 by nadesjar          #+#    #+#             */
/*   Updated: 2022/05/07 00:03:55 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_print_nbr_fd(int nbr, int fd)
{
	int	x;

	x = 0;
	if (nbr > 9)
		ft_print_nbr_fd(nbr / 10, fd);
	x = nbr % 10 + '0';
	ft_putchar_fd(x, fd);
}

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == 0)
		ft_putchar_fd('0', fd);
	if (nb != -2147483648)
	{
		if (nb < 0)
		{
			ft_putchar_fd('-', fd);
			nb = nb * -1;
		}
		if (nb)
			ft_print_nbr_fd(nb, fd);
	}
	else if (nb == -2147483648)
		write(fd, "-2147483648", 11);
}
