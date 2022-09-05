/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_only.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 12:18:44 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/05 12:18:54 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

bool	ft_is_only(char *buffer, char c)
{
	int i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] != c)
			return (false);
		i++;
	}
	return (true);
}
