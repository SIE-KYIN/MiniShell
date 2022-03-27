#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> 

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
** *****************************************
** *************DATASTRUCTURE***************
** *****************************************
*/

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
void	pre_traverse(t_tree *tree);

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
*/
char **ft_ms_split(char *line, t_list *env_list);
int cnt_delimiter(char *line);
int is_delimiter(char c, char next);


/*
** parse_envv.c
*/
t_list *parse_envv(char **envv);


/*
** tokenize.c
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
int str_in_quote(char *line, int i, int *single_flag, int *double_flag);
int str_in_quote2(char *line, int i, int single_flag, int double_flag);
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
** utils2.c  ++++++++3
*/
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);

/*
** utils3.c  ++++++++3
*/
char			**ft_split(char const *s, char c);
