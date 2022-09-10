/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/09 20:30:21 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../srcs/libft/libft.h"

# define DBQUOTE 34
# define SQUOTE 39

typedef struct		s_cmd
{
	char	*buffer;		//indivividual buffer
	char	**token;		//tokenized buffer
	
	char	*infile;		//for open input file
	int		fd_in;			//for open input file
	
	char	*outfile;		//for open output file
	char	*outappend;		//for open output file in append mode
	int		fd_out;			//for open output file
	
	int		file;			//for open input file
	int		file_error;		//for open error file
}					t_cmd;

typedef struct		s_data
{
	char	**env;			//copy of env
	char	*buffer;		//buffer for readline
	char	*prompt;		//prompt message for readline
	int 	cmd_count;		//count of commands
	char	expand[2];		//flag for expansion
	char	heredoc[2];		//flag for heredoc
	pid_t	*pid;			//pids for all process
	t_cmd	*cmd;			//array of cmd
}					t_data;

/** FONTIONS **/

void	ft_init_environement(t_data *data, char **env);
void	ft_exit(t_data *data, char *str, int s);
void	ft_print_table(t_data *data);
void	ft_free_table(t_data *data);

char	*ft_get_variable(t_data *data, char *buffer);
char	*ft_get_prompt(t_data *data);

/** PARSING **/

char	*ft_expand_heredoc(t_data *data, char *heredoc);
char	*ft_expand(t_data *data, char *token, int flag);
char	*ft_expand_variable(t_data *data, char *token);
char	*ft_remove_char(char *token, char sep);
char	*ft_trim_token(char *buffer, char sep);

void	ft_clean_token(t_data *data, char **token);
void	ft_make_token(t_data *data);
void 	ft_parse(t_data *data);

int		ft_token_count(char *buffer, char sep);

/** ENGINE **/

char	*ft_get_path(t_data *data, int nb);

void	ft_exec_cmd(t_data *data, char *cmd_path, int nb);
void	ft_make_child_process(t_data *data, int nb);
void	ft_find_redirect(t_data *data, int nb);
void	ft_fork_main(t_data *data, int nb);
void	ft_redirections(t_cmd *cmd);

bool	ft_execute_builtin(t_data *data, int nb);
bool	ft_check_builtin(t_data *data, int nb);

/** CMDS **/

void	ft_unset(t_data *data, char *buffer);
void	ft_export(t_data *data, char *arg);
void	ft_cd(t_data *data, char *buffer);
void	ft_heredoc(char *limiter, char *heredoc);
void	ft_env(t_data *data);
void	ft_echo(char **arg);

#endif
