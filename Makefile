# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gshim <gshim@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/22 17:48:50 by gshim             #+#    #+#              #
#    Updated: 2022/03/15 18:04:38 by gshim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
#CFLAGS = -Wall -Wextra -Werror -g
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

NAME = minishell

SRCS_DIR = ./src
SRCS = src/readline.c
OBJS = $(SRCS:.c=.o)

#======================= 외부라이브러리 모음 ==========================
LIB_NAME = ft
LIB_DIR = ./include/libft
LIB = $(addprefix $(LIB_DIR)/, libft.a)

#=================================================================

$(NAME) : $(OBJS)
	$(MAKE) -C $(LIB_DIR) bonus
	$(CC) $(CFLAGS) -L$(LIB_DIR) -l$(LIB_NAME) -lreadline \
					$^ -o $@

$(SRCS_DIR)/%.o : $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -I$(LIB_DIR) -c $< -o $@

all : $(NAME)

clean :
	rm -rf $(OBJS)
	$(MAKE) -C $(LIB_DIR) clean

fclean :
	rm -rf $(NAME) $(OBJS)
	$(MAKE) -C $(LIB_DIR) fclean

re : fclean all

.PHONY : all clean fclean re
