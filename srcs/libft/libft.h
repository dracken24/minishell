/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:00:19 by nadesjar          #+#    #+#             */
/*   Updated: 2022/09/06 11:40:07 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "./gnl/gnl.h"
# include <stddef.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdio.h>
# include <stdbool.h>


# define RED 1
# define GREEN 2
# define YELLOW 3
# define BLUE 4
# define PURPLE 5
# define CYAN 6
# define WHITE 7
# define RESET 8

typedef struct s_ct{
	int		i;
	int		k;
}	t_ct;

typedef struct s_list{
	void			*content;
	struct s_list	*next;
}					t_list;

size_t	ft_strlcat(char *dest, char *src, size_t size);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
size_t	ft_strlen(const char *str);
size_t	ft_fd_len(char *name, int fd_ext);

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);

int		ft_strncmp_tab(char **tab, char *str, size_t len, size_t nbr_turn);
int		ft_memcmp(const void *s1, const void *s2, size_t len);
int		ft_nbr_sign_in_str(const char *str, int c);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_nbr_sign_in_tab(char **tab, char c);
int		ft_array_size(char **array);
int		ft_open_fd(char *str, int i);
int		ft_atoi(const char *str);
int		ft_lstsize(t_list *lst);
int		ft_nbr_ptr(char **tab);
int		ft_p_or_imp(int nbr);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

bool	ft_strchr_bool(const char *str, int c);
bool	ft_tabchr(char **tab, char *find);
bool	ft_is_only(char *buffer, char c);

char	*ft_strnstr_ret_tofind(const char *str, const char *to_find, size_t len);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
char	*ft_strmapi(const char *str, char (*f)(unsigned int, char));
char	*ft_strchr_tab(char **tab, char **tab_2, size_t nbr_turn);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char *str1, char const *str2, int f);
char	**ft_split_cmd(char const *str, char c);
char	*ft_strrchr(const char *str, int c);
char	*ft_strchr(const char *str, int c);
char	*ft_strtok(char *buffer, char sep);
char	**ft_split(char const *s, char c);
void	ft_print_doc(char *str);
char	*ft_strdup(char *src);
char	*ft_itoa(int n);

void	ft_striteri(char *str, void (*f)(unsigned int, char *));
void	*ft_memmove(void *dest, const void *src, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t len);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	*ft_memchr(const void *src, int c, size_t n);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	*ft_memset(void *str, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *str, size_t len);
void	ft_putendl_fd(char *str, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_swap(int *a, int *b);
void	ft_free_ptr(char **tab);
void	ft_color(int color);

#endif
