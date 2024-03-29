# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dracken24 <dracken24@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 23:33:38 by root              #+#    #+#              #
#    Updated: 2023/01/13 17:29:55 by dracken24        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom du Projet
NAME = libft.a

# Flags
AR = ar
CC = gcc
ARFLAGS = rcs
CFLAGS = -Wall -Wextra -Werror -g

# Sources files
S = srcs/
SRCS_FILES = ft_isascii.c ft_strlcpy.c ft_toupper.c ft_memchr.c ft_memmove.c \
		ft_putnbr_fd.c ft_putendl_fd.c ft_lstmap.c ft_lstiter.c ft_lstclear.c \
		ft_strlen.c ft_putchar_fd.c ft_split.c ft_lstadd_front.c ft_strchr.c \
		ft_bzero.c ft_calloc.c ft_memcmp.c ft_strnstr.c ft_lstnew.c ft_itoa.c\
		ft_lstdelone.c ft_lstadd_back.c ft_lstlast.c ft_lstsize.c ft_atoi.c \
		ft_strcat.c ft_isalnum.c ft_putchar.c ft_memcpy.c ft_putstr_fd.c \
		ft_striteri.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_substr.c \
		ft_strncmp.c ft_isalpha.c ft_strlcat.c ft_tolower.c ft_memset.c \
		ft_isdigit.c ft_putstr.c ft_strrchr.c ft_isprint.c ft_strdup.c \
		ft_atoli.c ft_get_next_line.c ft_printf.c ft_printf_utils.c \
		ft_free_array.c ft_split_size.c ft_array_size.c ft_color.c \
		ft_is_only.c ft_strtok.c ft_remove_char.c ft_trim_token.c \
		ft_token_count.c ft_open_fd.c ft_remalloc.c ft_free.c ft_clear_fd.c \
		ft_check_closed_quote.c  ft_pipe_check.c\

SRCS = $(addprefix $S, $(SRCS_FILES))

# Objects conversion
O = objs/
OBJS= $(SRCS:$S%=$O%.o)
$O%.o: $S%
	@printf "$G■$W"
	@$(CC) $(CFLAGS) -c $< -o $@
	
# Main rule
all: init $(NAME)
	@echo "$G\n$(NAME) READY FOR NEXT!\n$W"

# Making objs folder
init:
	@mkdir -p $O
	@printf "$CCOMPILATION DE $(NAME)\n$W"

# Creating libft library
$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $@ $^

# Cleaning
REMOVE = rm -rf

clean:
	@$(REMOVE) $O

fclean: clean
	@$(REMOVE) $(NAME)

re:	fclean all

# Utilities
COMMIT = $(shell date "+%d %B %T")
git:
	@git add .
	@git commit -m "$(COMMIT)"
	@git push

R = $(shell tput -Txterm setaf 1)
G = $(shell tput -Txterm setaf 2)
C = $(shell tput -Txterm setaf 6)
W = $(shell tput -Txterm setaf 7)
