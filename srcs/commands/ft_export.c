/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:20:35 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/03 13:42:58 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	change_value(t_data *data, char *buffer, char **tab_, int i);
char	**alloc_tab(t_data *data, char *buffer);

bool	ft_export(t_data *data, t_cmd *cmd, char *buffer)
{
	char	**tab_;
	int		i;
	bool	ret;

	cmd->ct = 1;
	ret = 0;
	tab_ = alloc_tab(data, buffer);
	tab_ = ft_split(buffer, '=');
	i = -1;
	while (data->env[++i])
	{
		if (ft_strncmp(data->env[i], tab_[0], ft_strlen(tab_[0])) == 0)
		{
			ret = change_value(data, buffer, tab_, i);
			ft_free_ptr(tab_);
			return (true);
		}
	}
	if (ft_strchr_bool(buffer, '"') == true)
		ret = change_value(data, buffer, tab_, i);
	else
	{
		free(data->env[i]);
		data->env[i] = ft_strjoin(tab_[0], ft_strjoin("=", tab_[1], 0), 0);
	}
	data->env[++i] = NULL;
	ft_free_ptr(tab_);
	if (ret == false)
		return (false);
	return (true);
}

bool	change_value(t_data *data, char *buffer, char **tab_, int i)
{
	char	**tab_2;

	if (ft_strchr_bool(buffer, '"') == true)
	{
		tab_2 = ft_calloc(sizeof(char), ft_strlen(buffer - 2));
		if (!tab_2)
		{
			free(buffer);
			free(tab_2);
			ft_free_ptr(tab_);
			printf("Error, wrong alloc <change_value>\n");
			return (false);
		}
		tab_2 = ft_split(buffer, '"');
		free(data->env[i]);
		data->env[i] = ft_strjoin(tab_2[0], tab_2[1], 0);
		ft_free_ptr(tab_2);
	}
	else
	{
		free(data->env[i]);
		data->env[i] = ft_strjoin(tab_[0], ft_strjoin("=", tab_[1], 0), 0);
	}
	return (true);
}

char	**alloc_tab(t_data *data, char *buffer)
{
	static char	**tab_;

	tab_ = ft_calloc(sizeof(char *), 2);
	if (!tab_)
	{
		free(tab_);
		free(buffer);
		ft_free_ptr(data->env);
	}
	return (tab_);
}
