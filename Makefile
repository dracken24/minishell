# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 23:33:38 by root              #+#    #+#              #
#    Updated: 2022/09/11 18:34:36 by nadesjar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

P_OBJS 			= ./objs/
P_SRCS			= ./srcs/
P_UTILS			= ./srcs/utils/
P_INIT			= ./srcs/init/
P_KILL			= ./srcs/kill/
P_PARS			= ./srcs/parsing/
P_ENGINE		= ./srcs/engine/
P_COMM  		= ./srcs/commands/
P_BUILT  		= ./srcs/built_in/

FILES			= $(P_SRCS)minishell.c \
				$(P_KILL)exit.c \
				$(P_INIT)init.c \
				$(P_UTILS)utils.c $(P_UTILS)utils_02.c \
				$(P_UTILS)pipes.c \
				$(P_COMM)ft_cd.c $(P_COMM)ft_unset.c \
				$(P_COMM)echo_env.c $(P_COMM)ft_export.c \
				$(P_PARS)parsing_01.c $(P_PARS)parsing_02.c \
				$(P_ENGINE)engine.c $(P_ENGINE)check_path.c \
				$(P_COMM)heredoc.c \

OBJS 			= $(patsubst $(P_SRCS)%.c, $(P_OBJS)%.o, $(FILES)) \

CC 				= gcc
FLAGS 			= -Wall -Wextra -Werror
RLFLAGS 		= -lreadline -lncurses -g

NAME 			= minishell

LIBFT			= make_lib
LIBFT_A			= $(P_SRCS)libft/libft.a

all: signature make_lib $(NAME)

$(NAME): msg_in $(OBJS) msg_out
	@gcc $(OBJS) $(LIBFT_A) $(FLAGS) $(RLFLAGS) -o $(NAME)

$(P_OBJS)%.o:	$(P_SRCS)%.c
	@mkdir -p $(P_OBJS)
	@mkdir -p $(P_OBJS)utils
	@mkdir -p $(P_OBJS)init
	@mkdir -p $(P_OBJS)kill
	@mkdir -p $(P_OBJS)parsing
	@mkdir -p $(P_OBJS)engine
	@mkdir -p $(P_OBJS)commands
	@mkdir -p $(P_OBJS)built_in
	@$(CC) $(FLAGS) -I. -c $< -o $@
	@printf "$G■"

msg_in:
	@echo $L"COMPILATION DE MINISHELL..."$R

msg_out:
	@echo '\n'$G"COMPILATION COMPLETE :)\n"$R

make_lib:
	@$(MAKE) -s -C ./srcs/libft

clean:
	@rm -f $(OBJS)
	@rm -fr ./srcs/libft/objs ./objs
	@echo $G"\n                                   BYE BYE\n"$R

fclean: clean
	@$(MAKE) fclean -s -C ./srcs/libft
	@rm -f $(NAME)

re:	fclean all

signature:
	@echo "$G\n\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/"
	@echo " |             ---------------------------------------------             |"
	@echo " |             *--*          $LPROJET: MINISHELL$G          *--*             |"
	@echo " |             *--*      $LPAR: DANTREMB && NADESJAR$G      *--*             |"
	@echo " |             ---------------------------------------------             |"
	@echo "/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\ \n$W"
	
L	= $(shell tput -Txterm setaf 5)
R	= $(shell tput -Txterm setaf 1)
G	= $(shell tput -Txterm setaf 2)
C	= $(shell tput -Txterm setaf 6)
W	= $(shell tput -Txterm setaf 7)
	
.Phony: all make_lib msg_in msg_out clean fclean re signature

# 禡
