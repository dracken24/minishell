/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 11:19:48 by marvin            #+#    #+#             */
/*   Updated: 2022/05/07 00:03:13 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;
	t_list	*pos;

	i = 0;
	pos = lst;
	while (pos != NULL)
	{
		pos = pos->next;
		i++;
	}
	return (i);
}
