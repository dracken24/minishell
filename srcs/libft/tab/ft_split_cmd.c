/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:06:41 by nadesjar          #+#    #+#             */
/*   Updated: 2022/08/04 12:06:56 by nadesjar         ###   ########.fr       */
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

char	**ft_split_cmd(char const *str, char c)
{
	size_t	i;
	size_t	k;
	int		index;
	char	**tab;

	if (!str)
		return (NULL);
	tab = ft_calloc((ft_count_word(str, c) + 1), sizeof(char *));
	if (!tab)
		return (NULL);
	i = -1;
	k = 0;
	index = -1;
	while (++i <= ft_strlen(str))
	{
		if (str[i] == '"')
		{
			index = i + 1;
			i++;
			while (str[i] != '"')
				i++;
			tab[k++] = word_dup(str, index, i);
			index = -1;
		}
		else if (str[i] != c && index < 0)
			index = i;
		else if ((str[i] == c || i == ft_strlen(str)) && index >= 0)
		{
			tab[k++] = word_dup(str, index, i);
			index = -1;
		}
	}
	tab[k] = 0;
	return (tab);
}