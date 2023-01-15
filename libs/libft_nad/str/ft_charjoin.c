/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:03:09 by nadesjar          #+#    #+#             */
/*   Updated: 2022/10/21 13:14:43 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_charjoin(char a, char b)
{
	char	*ret;

	if (!a || !b)
		return (NULL);
	ret = ft_calloc(sizeof(char), 3);
	ret[0] = a;
	ret[1] = b;
	ret[2] = '\0';
	return (ret);
}
