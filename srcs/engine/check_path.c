/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 20:44:21 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/05 15:31:35 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_good_path(t_data *data, char **paths, char *env_path, int nb);
char	*find_path(char *env_path);

char	*ft_execute(t_data *data, int nb)
{
	char	**paths;
	char	*env_path;
	int		i;

	i = -1;
	while (data->env[++i])
	{
		env_path = ft_strnstr(data->env[i], "PATH=", 5);
		if (env_path)
		{
			env_path = find_path(env_path);
			break ;
		}
	}
	paths = ft_calloc(sizeof(paths), ft_strlen(env_path + 1));
	env_path = find_good_path(data, paths, env_path, nb);
	free(paths);
	return (env_path);
}

char	*find_path(char *env_path)
{
	char	*tmp;
	int		len;

	len = ft_strlen(env_path);
	tmp = ft_calloc(sizeof(tmp), len + 1);
	if (!tmp)
	{
		perror("Error, tmp <find_path>");
		free(tmp);
		return (NULL);
	}
	tmp = ft_substr(env_path, 5, len);
	len = ft_strlen(tmp);
	env_path = ft_substr(tmp, 0, len);
	free(tmp);
	return (env_path);
}

char	*find_good_path(t_data *data, char **paths, char *env_path, int nb)
{
	int i;
	char *cmd_path;
	
	if (!paths)
	{
		perror("Error, path <find_good_path>");
		return (NULL);
	}
	paths = ft_split(env_path, ':');
	i = -1;
	while (paths[++i])
		paths[i] = ft_strjoin(paths[i], "/", 0);
	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], data->cmd[nb].token[0], 0);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free(paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	return (NULL);
}
