/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_bool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:13:40 by nadesjar          #+#    #+#             */
/*   Updated: 2022/07/28 16:16:59 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_nbr_sign_in_str(const char *str, int c)
{
	int	i;
	int	ret;

	ret = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == (char)c)
			ret += 1;
	}
	return (ret);
}
