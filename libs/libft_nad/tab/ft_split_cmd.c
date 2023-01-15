/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:06:41 by nadesjar          #+#    #+#             */
/*   Updated: 2022/12/14 00:06:31 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_count_word(char const *src, char sep)
{
	int		words;

	words = 0;
	while (*src)
	{
		while (*src == sep)
			src++;
		if (*src != sep && *src)
			words++;
		while (*src != sep && *src)
			src++;
	}
	return (words);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = ft_calloc((finish - start + 1), sizeof(char));
	if (!word)
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

void	ft_split_while(t_lct *ct, char **tab, char const *str, char c)
{
	if (str[ct->i] == '"')
	{
		ct->index = ct->i + 1;
		ct->i++;
		while (str[ct->i] != '"')
			ct->i++;
		tab[ct->k++] = word_dup(str, ct->index, ct->i);
		ct->index = -1;
	}
	else if (str[ct->i] != c && ct->index < 0)
		ct->index = ct->i;
	else if ((str[ct->i] == c || ct->i == ft_strlen(str)) && ct->index >= 0)
	{
		tab[ct->k++] = word_dup(str, ct->index, ct->i);
		ct->index = -1;
	}
}

char	**ft_split_cmd(char const *str, char c)
{
	t_lct	ct;
	char	**tab;

	if (!str)
		return (NULL);
	tab = ft_calloc((ft_count_word(str, c) + 1), sizeof(char *));
	if (!tab)
		return (NULL);
	ct.i = -1;
	ct.k = 0;
	ct.index = -1;
	while (++ct.i <= ft_strlen(str))
	{
		ft_split_while(&ct, tab, str, c);
	}
	tab[ct.k] = 0;
	return (tab);
}
