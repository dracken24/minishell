/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:57:35 by dantremb          #+#    #+#             */
/*   Updated: 2023/01/15 15:16:37 by dracken24        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* On recois 2 pointer sur des chaines de caractère que l'on doit placer "s2" */
/* a la suite de "s1" dans une nouvelle chaine et ensuite renvoyer un pointer */
/* a celui-ci. On alloue la memoire à "tmp" avec la longueur de "s1" + "s2"   */
/* On retoure NULL si l'allocation ne fonctionne pas. On copie ensuite les 	  */
/* caractère de "s1" dans "tmp" et ensuite "s2" dans "tmp" a la suite en      */
/* gardant le meme compteur. On referme la chaine de caractère et on retourne */
/* le pointer sur "tmp"														  */

#include "../includes/libft.h"

char	*ft_strjoin(char *s1, char *s2, int f)
{
	char	*tmp;
	int		is;
	int		id;

	is = 0;
	id = 0;
	if (!s1 || !s2)
		return (NULL);
	tmp = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (tmp == NULL)
		return (NULL);
	while (s1 && s1[is])
	{
		tmp[is] = s1[is];
		is++;
	}
	while (s2 && s2[id])
		tmp[is++] = s2[id++];
	tmp[is] = '\0';
	if (f == 1)
		free(s1);
	if (f == 2)
		free(s2);
	return (tmp);
}
