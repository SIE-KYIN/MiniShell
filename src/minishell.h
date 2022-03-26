/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:21:43 by gshim             #+#    #+#             */
/*   Updated: 2022/03/26 21:46:53 by gshim            ###   ########.fr       */
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
# include <fcntl.h> // 파일모드를위해추가

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

enum e_node_flag
{
	DELIMITER = 0, // 구분문자(> , < , | , >> , <<)
	COMMON_BUILTIN, // echo, cd, pwd, export, unset, env, exit
	FILE_NAME, // 리디렉션 대상
};

enum e_delimiter_flag
{
	SINGLE_REDIR_INPUT = 0,
	DOUBLE_REDIR_INPUT,
	SINGLE_REDIR_OUPUT,
	DOUBLE_REDIR_OUTPUT,
	PIPE,
};

typedef struct s_tree_node
{
	int flag;//무슨 노드인지
	char **command;
	struct s_tree_node* left;
	struct s_tree_node* right;
} t_tree_node;

typedef struct s_tree
{
	struct s_tree_node* root_node;
} t_tree;


/*
** DataStucture-LinkedList1
*/
void add_node(t_list* list, int position, char *var, char *data);
t_list_node* get_node(t_list* list, int position);
void remove_node(t_list* list, int position);
void displayDoublyList(t_list* pList); // 삭제예정
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
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char *ft_colorstr(char *str);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);

/*
** utils3.c  ++++++++3
*/
int is_delimiter(char c, char next);
char			**ft_split(char const *s, char c);
char **ft_ms_split(char *line);
int cnt_delimiter(char *line);

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
//void parse_line(t_tree *tree, char **env);
void read_line(t_list *env_list, char **line);
void parse_line(t_tree *tree, char **env);

/*
** check_syntax.c
*/
int check_syntax(char *line);

/*
** tokenize.c
*/
t_tree *tokenize(char *line);



/*
** b_tree.c
*/
t_tree*		create_tree();
t_tree_node*	insert_root(t_tree* tree, char **command, int flag);
t_tree_node*	insert_left(t_tree_node* parent,  char **command, int flag);
t_tree_node*	insert_right(t_tree_node* parent, char **command, int flag);
void	delete_tree(t_tree* tree);

void	post_traverse(t_tree *tree);
void	in_traverse(t_tree *tree);
void	pre_traverse(t_tree *tree, char **env);

// gshim
int		execute(char *command, char **arg, char **env);
void	ft_echo(char *argv[], char **env);
void	ft_cd(char *argv[], char **env);
void	ft_pwd();
void	ft_export(char **env);
void	ft_unset(char **env);
void	ft_env(char **env);
int		redir_out(t_tree_node *root, t_tree_node *left);
int		redir_in(t_tree_node *root, t_tree_node *right);
//int redir_in(char **cmdvector);
int		execute_builtin(char *command, char **arg, char **env);
//void exit(char **env);
char **gather(t_list *list);

#endif
