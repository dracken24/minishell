/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/26 12:58:43 by nadesjar         ###   ########.fr       */
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
	char	**cmds;			//all builtin names
	char	**env;			//copy of env
	char	*start_path;
	char	*buffer;		//buffer for readline
	char	*prompt;		//prompt message for readline
	char	expand[2];		//flag for expansion
	char	heredoc;		//flag for heredoc
	
	int 	cmd_count;		//count of commands
	int		ct;
	
	pid_t	*pid;			//pids for all process
	t_cmd	*cmd;			//array of cmd
}					t_data;

/** FONTIONS **/

void	ft_init_environement(char **env);
void	ft_sig(int ac, char **argv);
void	ft_exit(char *str, int s);
void	handle_sigint(int sig);
void	ft_print_table(void);
void	ft_free_table(void);
void	ft_quit(char *str);

char	*ft_get_variable(char *buffer);
char	*ft_get_prompt(void);

/** HISTORY & SAVE ENV **/

void	ft_add_history(char *name);
void	ft_save_env(char *name);
void	ft_moove_history(void);
void	ft_fd_env(char *name);
void	ft_save_history(void);

bool	ft_refresh_history(int fd);

/** PARSING **/

char	*ft_remove_char(char *token, char sep);
char	*ft_trim_token(char *buffer, char sep);
char	*ft_expand_heredoc(char *heredoc);
char	*ft_expand(char *token, int flag);
char	*ft_expand_variable(char *token);

void	ft_clean_token(char **token);

int		ft_token_count(char *buffer, char sep);
int		ft_make_token(void);
int		ft_parse(void);

/** ENGINE **/

char	*ft_get_path(int nb);

void	ft_exec_cmd(char *cmd_path, int nb);
void	ft_make_child_process(int nb);
void	ft_redirections(t_cmd *cmd);
void	ft_find_redirect(int nb);
void	ft_fork_main(int nb);
void	ft_keep_cmd(int nb);

bool	ft_check_builtin(int nb, int i);
bool	ft_execute_builtin(int nb);

/** CMDS **/

void	ft_heredoc(char *limiter, char *heredoc);
void	ft_unset(char *buffer, int nb);
void	ft_export(char *arg, int nb);
void	ft_cd(char *buffer);
void	ft_echo(char **arg);
void	ft_env(void);

#endif
