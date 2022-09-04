/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/04 16:06:42 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
// # include <stdio.h>
// # include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../srcs/libft/libft.h"
// # include <stdbool.h>

#define DBQUOTE 34
#define SQUOTE 39
#define SPCE 32

typedef struct		s_cmd
{
	char	*buffer;		//indivividual buffer
	char	**token;		//tokenized buffer
	char	*path;			//for execve path
	int		ct;
	int		nbr_token;
	int		no_cmd;
	int		infile;			//for open input file
	int		outfile;		//for open output file
}					t_cmd;

typedef struct		s_data
{
	int		i;
	int		k;
	char	*str;
	char	**env;			//copy of env
	char	*buffer;		//buffer for readline
	char	*prompt;		//prompt message for readline
	int 	cmd_count;		//count of commands
	t_cmd	*cmd;			//array of cmd

}					t_data;

void	ft_init_environement(t_data *data, char **env);
void	ft_exit(t_data *data, char *str, int s);
void	ft_copy_env(t_data *data, char **env);

bool	ft_is_only_space(char *buffer);

char	*ft_get_prompt(t_data *data);

/** PARSING **/

char	*ft_get_variable(t_data *data, char *buffer);
char	*ft_strtok(char *buffer, char sep);
char	*ft_trim_space(char *buffer);

void	ft_print_variable(t_data *data, char *buffer);
void	ft_make_cmd_table(t_data *data);
void	ft_redirect_before(t_cmd *cmd);
void	ft_redirect_after(t_cmd *cmd);
void	free_redirect(char **options);
void	ft_print_table(t_data *data);
void	ft_make_token(t_data *data);
void	ft_free_pars(t_data *data);
void	ft_redirections(t_cmd *cmd);
void	ft_open_fds(t_data *data);
void 	ft_parse(t_data *data);

int		ft_token_count(char *buffer, char sep);

/** Builtin **/

void	ft_execute_builtin(t_data *data, t_cmd *cmd);
void	ft_execute_table(t_data *data);

/** CMDS **/

bool	ft_export(t_data *data, t_cmd *cmd, char *buffer);
bool	ft_unset(t_data *data, t_cmd *cmd, char *buffer);
bool	ft_cd(t_data *data, t_cmd *cmd, char *buffer);
bool	ft_pwd(t_data *data, t_cmd *cmd);

bool	ft_cat(t_cmd *cmd);

void	ft_echo(t_data *data, t_cmd *cmd, char *buffer);
void	ft_redirect_output_append(t_cmd *cmd);
void	ft_env(t_data *data, t_cmd *cmd);
void    ft_grep(t_cmd *cmd);
void	ft_wc(t_cmd *cmd);

#endif
