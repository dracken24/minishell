/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 03:31:08 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/04 16:05:45 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_print_nbr(int nbr)
{
	int	x;
	
	if (nbr > 9)
		ft_print_nbr(nbr / 10);
	x = nbr % 10 + '0';
	ft_putchar(x);
}

void	ft_ptnbr(int nbr)
{
	if(nbr == 0)
		ft_putchar('0');
	else if (nbr != -2147483648)
	{
		if (nbr < 0)
		{
			ft_putchar('-');
			nbr *= -1;
		}
		ft_print_nbr(nbr);
	}
	else if (nbr == -2147483648)
		write(1, "-2147483648", 11);
}

int ft_atoi(const char *str)
{
	int i;
	int less;
	int ret;

	ret = 0;
	less = 1;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			less = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		ret = (ret * 10) + (str[i] - 48);
		i++;
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (ret * less);
	}
	return (0);
}

void sighandler(int);

int main()
{
	signal(SIGINT, sighandler);

	while (1)
	{
		printf("Going to sleep for a second...\n");
		sleep(1);
	}
	return (0);
}

void sighandler(int signum)
{
	printf("Caught signal %d, coming out...\n", signum);
	exit(1);
}