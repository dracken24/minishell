/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 20:44:21 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/05 15:20:34 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_good_path(t_data *data, char **paths, char *env_path, int nb);
char	*find_path(t_data *data, char *env_path, int nb);

char	*ft_execute(t_data *data, int nb)
{
	char	**paths;
	char	*cmd_path;
	char	*env_path;
	int		i;

	cmd_path = NULL;
	paths = NULL;
	i = -1;
	printf("1\n");
	while (data->env[++i])
	{
		env_path = ft_strnstr(data->env[i], "PATH=", 5);
		if (env_path)
		{
			env_path = find_path(data, env_path, nb);
			break ;
		}
	}
	printf("1.1\n");

	paths = ft_calloc(sizeof(paths), ft_strlen(env_path + 1));
	printf("1.2\n");
	cmd_path = find_good_path(data, paths, env_path, nb);
	printf("1.3\n");
	free(paths);
	return (cmd_path);
}

char	*find_path(t_data *data, char *env_path, int nb)
{
	(void)data;
	(void)nb;
	char	*tmp;
	int		len;

	len = ft_strlen(env_path);
	tmp = ft_calloc(sizeof(tmp), len + 1);
	if (!tmp)
	{
		perror("Error, tmp <find_path>");
		free(tmp);
		// exit(0);
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
		// exit(0);
	}
	printf("env_path: %s\n", env_path);
	paths = ft_split(env_path, ':');
	printf("2\n");
	i = -1;
	while (paths[++i])
		paths[i] = ft_strjoin(paths[i], "/", 0);
	printf("2.1\n");
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
	printf("2.2\n");
	return (NULL);
}
