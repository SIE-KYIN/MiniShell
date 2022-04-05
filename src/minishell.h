/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:21:43 by gshim             #+#    #+#             */
/*   Updated: 2022/04/05 16:36:31 by gshim            ###   ########.fr       */
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
# include <errno.h>

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
	DELIMITER = 0, // 구분문자(> , < , | , >> , <<
	COMMON_BUILTIN, // echo, cd, pwd, export, unset, env, exit
	FILE_NAME, // 리디렉션 대상
};

enum e_delimiter_flag
{
	SINGLE_REDIR_INPUT = 0,

	PIPE=4,
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
** *****************************************
** *************DATASTRUCTURE***************
** *****************************************
*/
int str_in_quote2(char *line, int i);
/*
** LinkedList1
*/
void add_node(t_list* list, int position, char *var, char *data);
t_list_node* get_node(t_list* list, int position);
void remove_node(t_list* list, int position);
void displayDoublyList(t_list* pList); // 삭제예정
int get_position(t_list *list, char *str);


/*
** LinkedList2
*/
t_list	*create_list(void);
void delete_list(t_list *list);

/*
** tree1
*/
t_tree_node*	insert_root(t_tree* tree, char **command, int flag);
t_tree_node*	insert_left(t_tree_node* parent,  char **command, int flag);
t_tree_node*	insert_right(t_tree_node* parent, char **command, int flag);
void	pre_traverse(t_tree *tree, t_list *env);
void	_pre_traverse(t_tree_node *root, t_list *env, char parent);

/*
** tree2
** +1
*/
t_tree*		create_tree();
void	delete_tree(t_tree* tree);

/*
** *****************************************
** ****************Parsing******************
** *****************************************
*/

/*
** check_syntax.c
** +3
*/
int check_syntax(char *line);

/*
** ft_ms_split.c
** +4
*/
char **ft_ms_split(char *line, t_list *env_list);


/*
** parse_envv.c
** +1
*/
t_list *parse_envv(char **envv);


/*
** tokenize.c
** +2
*/
t_tree *tokenize(char *line, t_list *env_list);


/*
** *****************************************
** ****************Prompt*******************
** *****************************************
*/

/*
** readline.c
*/
int read_line(t_list *env_list, char **line);


/*
** readline_utils.c
*/
void sig_int(int sig);
void sigHandler();
void	set_signal();
void	disable_signal();
char *ft_colorstr(char *str);


/*
** *****************************************
** ****************Utilities****************
** *****************************************
*/

/*
** utils1.c
*/
void ft_error(int flag);
char	*ft_strndup(char *src, int from, int to);
int is_same(char *str1, char *str2);
void print_intro();

/*
** utils2.c
** related to check_syntax.c
*/
int str_in_quote(char *line, int i, int single_flag, int double_flag);
int is_valid_s_c(char c);

/*
** utils3.c
** related to ft_ms_split.c
*/
int is_delimiter(char c, char next);
int cnt_delimiter(char *line);
void change_str(t_list *env_list, char **line, int fst, int sec);
int strcnt_double_ptr(char **ret);
char *ft_emptystr();

/*
** utils4.c
** related to ft_ms_split.c
*/
char **plus_space(char **str, int criteria);
void divide_str(char **ret, int i);

/*
** utils5.c
** related to tokenize.c
*/
int is_there_space(char *line);
char **find_cmd(char *line);
int token_cnt(char **token);
int is_there_delimiter(char **token);
int get_latest_token_loc(char **token);
int token_cnt(char **token);

char			**ft_cmd_split(char *s, char c);

/*
** *****************************************
** ****************gshim********************
** *****************************************
*/

// ft_export.c
int		ft_export(char *argv[], t_list *env);

// ft_echo.c
int		ft_echo(char *argv[]);

int		execute(char **arg, t_list *env);
int		ft_cd(char *argv[], t_list *env);
int		ft_pwd();
int		ft_unset(char *argv[], t_list *env);
int		ft_env(t_list *env);
int		ft_exit(char *argv[], t_list *env);
int		redir_out(t_tree_node *root, t_tree_node *left, bool flag);
int		redir_in(t_tree_node *root, t_tree_node *right, bool flag);
void	heredoc(t_tree_node *root, t_tree_node *right, int fd);
int		execute_builtin(char **arg, t_list *env);
//void exit(char **env);
char **gather(t_list *list);
int ft_pipe(t_tree_node *root, t_list *env);
int ft_command(t_tree_node *root, t_list *env);

t_list_node *search_node(t_list* list, char *var);
void delete_node(t_list* list, char *var);
void free_node(t_list_node *node);

int		get_status(int status);
void	set_status(t_list *env, int status);

#endif
