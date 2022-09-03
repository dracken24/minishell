/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:46:36 by marvin            #+#    #+#             */
/*   Updated: 2022/05/07 00:02:19 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_transfert(char *x, unsigned int number, long int len)
{
	while (number > 0)
	{
		x[len--] = 48 + (number % 10);
		number = number / 10;
	}
	return (x);
}

static long int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*str;
	long int		len;
	unsigned int	numb;

	len = ft_len(n);
	str = ft_calloc((len + 1), sizeof(char));
	if (!(str))
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		numb = n * -1;
		str[0] = '-';
	}
	else
		numb = n;
	str = ft_transfert(str, numb, len);
	return (str);
}
