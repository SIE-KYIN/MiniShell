# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gshim <gshim@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/22 17:48:50 by gshim             #+#    #+#              #
#    Updated: 2022/04/08 10:25:09 by gshim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
#CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

NAME = minishell

SRCS_DIR = ./src
SRCS =  src/DataStructure/linkedlist1.c src/DataStructure/linkedlist2.c src/DataStructure/linkedlist3.c \
	src/DataStructure/tree1.c src/DataStructure/tree2.c  src/DataStructure/tree3.c\
	src/Parsing/parse_envv.c src/Parsing/check_syntax.c \
	src/Parsing/tokenize.c src/Parsing/ft_ms_split.c \
	src/Utilities/utils1.c src/Utilities/utils2.c \
	src/Utilities/utils3.c src/Utilities/utils4.c \
	src/Utilities/utils5.c src/Utilities/utils6.c \
	src/Utilities/utils7.c src/Utilities/utils8.c \
	src/minishell.c \
	src/Prompt/readline.c src/Prompt/readline_utils.c  src/Prompt/readline_utils2.c\
	src/Redirect/redirect.c src/Redirect/ft_pipe.c \
	src/Redirect/heredoc.c \
	src/BuiltIn/builtIn.c src/BuiltIn/ft_export.c src/BuiltIn/ft_echo.c \
	src/BuiltIn/status.c src/BuiltIn/ft_cd.c src/BuiltIn/ft_exit.c src/BuiltIn/ft_execute.c
OBJS = $(SRCS:.c=.o)

#======================= 외부라이브러리 모음 ==========================
LIB_NAME = ft
LIB_DIR = ./include/libft
LIB = $(addprefix $(LIB_DIR)/, libft.a)

USER = gshim
#USER = kyujlee

RL_CLUSTER_L = -L/Users/${USER}/.brew/opt/readline/lib
RL_CLUSTER_I = -I/Users/${USER}/.brew/opt/readline/include
RL_MYMAC_L = -L/opt/homebrew/opt/readline/lib
RL_MYMAC_I = -I/opt/homebrew/opt/readline/include
#=================================================================

#=======================   데코레이터 모음   =========================

SHELL	= /bin/bash
sp		= /-\|/
idx		= 0

#=================================================================

$(NAME) : $(OBJS)
	$(MAKE) -C $(LIB_DIR) all
	$(CC) $(CFLAGS) -L$(LIB_DIR) -l$(LIB_NAME) \
	-lreadline $(RL_CLUSTER_L) $^ -o $@

$(SRCS_DIR)/%.o : $(SRCS_DIR)/%.c
	$(eval idx = $(shell expr $(idx) + 1))
	$(eval t_idx = $(shell expr $(idx) % 4 + 1))
	$(eval chr = $(shell echo $(sp) | cut -c $(t_idx)))
	@if [ $(idx) = 1 ]; then\
		echo -n "☕️ ☕️ MINISHELL Loading ...\n";\
	fi
	@printf "\b$(chr)"
	@$(CC) $(CFLAGS) -I$(LIB_DIR) $(RL_CLUSTER_I) -c $< -o $@

all : $(NAME)

clean :
	rm -rf $(OBJS)
	$(MAKE) -C $(LIB_DIR) clean

fclean :
	rm -rf $(NAME) $(OBJS)
	$(MAKE) -C $(LIB_DIR) fclean

re : fclean all

.PHONY : all clean fclean re
