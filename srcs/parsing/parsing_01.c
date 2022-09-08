/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:48:32 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/07 21:06:49 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_trim_token(char *buffer, char sep)
{
	int		i;

	if (!buffer)
		return (buffer);
	i = ft_strlen(buffer) - 1;
	while (buffer[i] == sep)
	{
		buffer[i] = '\0';
		i--;
	}
	while (*buffer == sep)
		buffer++;
	return (buffer);
}

int	ft_token_count(char *buffer, char sep)
{
	char	*tmp;
	char	*token;
	int		i;

	i = 0;
	tmp = ft_strdup(buffer);
	token = ft_trim_token(ft_strtok(tmp, sep), ' ');
	while (token)
	{
		i++;
		token = ft_trim_token(ft_strtok(NULL, sep), ' ');
	}
	free(tmp);
	return (i);
}

void	ft_remove_char(char *token, char sep)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == sep)
		{
			j = i;
			while (token[j])
			{
				token[j] = token[j + 1];
				j++;
			}
		}
		else
			i++;
	}
}

char	*ft_expand_variable(t_data *data, char *token)
{
	ft_color(YELLOW);
	if (token[0] == '$' && ft_strchr(&token[1], '$') == NULL)
		token = ft_get_variable(data, &token[1]);
	else
		printf("expander !!!!\n");
	ft_color(WHITE);
	return (token);
}
