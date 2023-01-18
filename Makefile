# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nadesjar <dracken24@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 23:33:38 by root              #+#    #+#              #
#    Updated: 2023/01/17 11:58:10 by nadesjar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

P_OBJS 			= ./objs/
P_SRCS			= ./srcs/
P_UTILS			= ./srcs/utils/
P_LIBFT			= ./libs/libft/

FILES			= $(P_SRCS)minishell.c \
				$(P_UTILS)builtins.c $(P_UTILS)engine.c\
				$(P_UTILS)execute.c $(P_UTILS)parsing.c \
				$(P_UTILS)signals.c $(P_UTILS)tokens.c \
				$(P_UTILS)validation.c $(P_UTILS)keep_history.c \
				$(P_UTILS)prompt.c \

OBJS 			= $(patsubst $(P_SRCS)%.c, $(P_OBJS)%.o, $(FILES)) \

CC 				= gcc
FLAGS 			= -Wall -Wextra -Werror
RLFLAGS 		= -lreadline -lncurses 

NAME 			= DrackenShell

LIBFT			= make_lib
LIBFT_A			= $(P_LIBFT)/libft.a libs/readline/libreadline.a

all: signature make_lib $(NAME)

$(NAME): msg_in $(OBJS) msg_out
	@gcc $(OBJS) $(LIBFT_A) $(FLAGS) $(RLFLAGS) -g -o $(NAME)

$(P_OBJS)%.o:	$(P_SRCS)%.c
	@mkdir -p $(P_OBJS)
	@mkdir -p $(P_OBJS)utils
	@$(CC) $(FLAGS) -I. -c $< -o $@
	@printf "$G■"

msg_in:
	@echo $L"COMPILATION DE MINISHELL..."$R

msg_out:
	@echo '\n'$G"COMPILATION COMPLETE :)\n"$R

make_lib:
	@$(MAKE) -s -C ./libs/libft

clean:
	@rm -f $(OBJS)
	@rm -fr ./libs/libft/objs ./objs
	@echo $G"\n                                   BYE BYE\n"$R

fclean: clean
	@$(MAKE) fclean -s -C ./libs/libft
	@rm -f $(NAME)

re:	fclean all

signature:
	@echo "$G\n\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/"
	@echo " |             ---------------------------------------------             |"
	@echo " |             *--*          $LPROJET: MINISHELL$G          *--*             |"
	@echo " |             *--*            $LPAR: NADESJAR$G            *--*             |"
	@echo " |             ---------------------------------------------             |"
	@echo "/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\ \n$W"
	
L	= $(shell tput -Txterm setaf 5)
R	= $(shell tput -Txterm setaf 1)
G	= $(shell tput -Txterm setaf 2)
C	= $(shell tput -Txterm setaf 6)
W	= $(shell tput -Txterm setaf 7)
	
.Phony: all make_lib msg_in msg_out clean fclean re signature
