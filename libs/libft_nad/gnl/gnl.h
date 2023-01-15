/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:12:33 by nadesjar          #+#    #+#             */
/*   Updated: 2022/12/13 23:30:08 by nadesjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

size_t	ft_slen(char *str);

char	*ft_read_fd(int fd, char *save_str);
char	*ft_strjoinn(char *save_str, char *buff);
char	*ft_strchrr(char *str, int c);
char	*ft_get_nline(char *save_str);
char	*ft_get_line(char *save_str);
char	*get_next_line(int fd);

#endif
