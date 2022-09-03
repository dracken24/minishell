/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:55:46 by nadesjar          #+#    #+#             */
/*   Updated: 2022/07/29 11:56:20 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	check_entry(char *str, char *base)
{
	int	i;
	int	k;

	if (!str || !base)
		return (0);
	i = -1;
	while (base[++i] != '\0')
	{
		k = i + 1;
		while (base[++k] != '\0')
			if (base[i] == base[k])
				return (0);
	}
	return (1);
}

int	check_before(char *str)
{
	int	k;

	k = 0;
	while ((str[k] >= 9 && str[k] <= 13) || str[k] == 32)
		k++;
	if (str[k] == '-')
		return (-1);
	return (1);
}

int	ft_add(char c, char *base)
{
	int	i;

	i = 0;
	while (c != base[i])
		i++;
	return (i);
}

int	check_in_base(char c, char *base)
{
	int	i;

	i = -1;
	while (base[++i])
	{
		if (c == base[i])
			return (1);
	}
	return (0);
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	ret;
	int	minus;
	int	divider;

	ret = 0;
	divider = ft_strlen(base);
	i = check_entry(str, base);
	if (i == 0)
	minus = check_before(str);
	i = -1;
	while (str[++i] != '\0' && check_in_base(str[i], base) == 1)
	{
		ret *= divider;
		ret += ft_add(str[i], base);
	}
	return (ret * minus);
}