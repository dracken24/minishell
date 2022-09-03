/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:22:16 by nadesjar          #+#    #+#             */
/*   Updated: 2022/08/27 14:58:50 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char **environ;

// < infile wc
// wc < infile
// < infile cat
// cat < infile

// bash-3.2$ cat <<SALUT
// > toto
// > lala
// > gggggg ggggg
// > SALUT
// toto
// lala
// gggggg ggggg
// bash-3.2$

bool	ft_redirect(t_data *data, char *buffer) 
{
	bool	ret;
	ret = 0;
	if (ft_strchr_bool(buffer, '>') == true)
		ret = ft_redirect_out(data, buffer);
	else if (ft_strchr_bool(buffer, '<') == true)
		ret = ft_redirect_input(data, buffer);
	return (ret);
}

bool	ft_redirect_input(t_data *data, char *buffer) 
{
	(void)data;
	char	**tab_;
	int		i;
	
	tab_ = ft_split(buffer, ' ');
	if (tab_[1][0] == '<' && tab_[1][1] == '<' && tab_[1][2] != '\0')
	{
		ft_redirect_input_heredoc(tab_[1] + 2);
		ft_free_ptr(tab_);
		return (true);
	}
	else if (tab_[0][0] == '<')
		tab_[0] = ft_strjoin(tab_[2], ft_strjoin(" ", tab_[1], 1), 1);
	else
	{
		i = 0;
		while (tab_[i][0] != '<')
			i++;
		i++;
		tab_[0] = ft_strjoin(tab_[0], ft_strjoin( " ", tab_[i], 1), 1);
	}
	// choose_cmd(data, tab_[0]);
	ft_free_ptr(tab_);
	return (true);
}

bool	ft_redirect_input_heredoc(char *limiter)
{
	char	*str;
	int		fd;

	fd = ft_open_fd("heredoc", 2);
	if (fd == -1)
		return (false);
	str = readline("<heredoc> ");
	while (str)
	{
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0
			&& str[ft_strlen(limiter)] == '\0')
			break;
		ft_putstr_fd(str, fd);
		ft_putchar_fd('\n', fd);
		free(str);
		str = readline("<heredoc> ");
	}
	close(fd);
	free(str);
	return (true);
}
