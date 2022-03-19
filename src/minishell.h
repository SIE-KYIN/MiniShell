/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:21:43 by gshim             #+#    #+#             */
/*   Updated: 2022/03/19 02:37:10 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../include/libft/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>

// gshim
int execute(char *command, char **arg, char **env);
void ft_echo(char *argv[], char **env);
void ft_cd(char *argv[], char **env);
void ft_pwd();
void ft_export(char **env);
void ft_unset(char **env);
void ft_env(char **env);
//void exit(char **env);

// kyujlee
typedef struct s_list_node
{
	char *var;
    char *data;
	struct s_list_node* prev;
	struct s_list_node* next;
} t_list_node;

typedef struct s_list
{
	int	cnt;
	struct s_list_node	top;
} t_list;

/*
** DataStucture-LinkedList1
*/
void add_node(t_list* list, int position, char *var, char *data);
t_list_node* get_node(t_list* list, int position);
void remove_node(t_list* list, int position);
void displayDoublyList(t_list* pList);
int get_position(t_list *list, char *str);


/*
** DataStucture-LinkedList2
*/
t_list	*create_list(void);
void delete_list(t_list *list);


/*
** utils1.c
*/
char	*ft_strndup(const char *src, int from, int to);
void ft_error(int flag);
int is_same(char *str1, char *str2);
void print_intro();


/*
** utils2.c  ++++++++3
*/
char *ft_colorstr(char *str);
char	*ft_strjoin(char const *s1, char const *s2);

/*
** parse_envv.c
*/
t_list *parse_envv(char **envv);


/*
** ms_sighandle.c
*/
void sig_int(int sig);
void sigHandler();


/*
** readline.c
*/
void read_line(t_list *env_list, char *line, char **envv);

#endif
