/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 03:22:23 by nadesjar          #+#    #+#             */
/*   Updated: 2022/12/14 03:25:49 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_trim_token(char *token, char sep)
{
	int	i;

	if (!token)
		return (token);
	i = ft_strlen(token) - 1;
	while (token[i] == sep)
	{
		token[i] = '\0';
		i--;
	}
	while (*token == sep)
		token++;
	return (token);
}
