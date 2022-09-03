/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 12:43:11 by marvin            #+#    #+#             */
/*   Updated: 2022/05/07 00:03:20 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;

	if (!lst)
		return (NULL);
	if (!lst)
	{
		ft_lstdelone(lst, *del);
		return (NULL);
	}
	newlist = ft_lstnew(f(lst->content));
	lst = lst->next;
	while (lst)
	{
		ft_lstadd_back(&newlist, ft_lstnew(f(lst->content)));
		lst = lst->next;
	}
	return (newlist);
}
