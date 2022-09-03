/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:56:59 by nadesjar          #+#    #+#             */
/*   Updated: 2022/08/31 05:40:12 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// >> = ajouter ligne    > = ecrase fichier

bool	ft_redirect_out_trunk(t_data *data, t_cmd *cmd)
{
	(void)data;
	cmd->outfile = ft_open_fd(cmd->options[ft_nbr_ptr(cmd->options) - 2], 2);
	if (!cmd->outfile)
	{
		red();
		printf("error, wrong open\n");
		return (false);
	}
	dup2(cmd->outfile, STDOUT_FILENO);
	return (true);
}



bool	ft_redirect_output(t_data *data, char **options, int *fd)
{
	(void)data;
	int	rd;

	rd = open(options[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (rd < 0)
	{
		free(options);
		free(fd);
		printf("Error, wrong open <redirect_one>\n");
		return (false);
	}
	dup2(rd, STDOUT_FILENO);
	// choose_cmd(data, ft_strjoin(options[0], ft_strjoin(" ", options[1], 1), 1));
	dup2(fd[1], STDOUT_FILENO);
	ft_free_ptr(options);
	free(fd);
	close(rd);
	return (true);
}

bool	ft_redirect_out(t_data *data, char *buffer)
{
	char	**options;
	int		*fd;
	bool	ret;

	ret = 0;
	fd = ft_calloc(sizeof(int), 2);
	options = ft_split_cmd(buffer, ' ');
	if (!options || !fd)
	{
		ft_free_ptr(options);
		free(fd);
		printf("Error, wrong alloc <ft_redirect>\n");
		return (false);
	}
	else if (options[2][0] == '>' && options[2][1] == '\0')
		ret = ft_redirect_output(data, options, fd);
	else if (options[2][0] == '>' && options[2][1] == '>' && options[2][2] == '\0')
		ret = ft_redirect_output_append(data, options, fd);
	return (ret);
}
