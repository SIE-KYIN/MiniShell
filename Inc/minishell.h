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

typedef struct s_tree_node
{
	int flag;//무슨 노드인지
	char *command; //명령어, 구분문자 여기들어갈듯
	char *argument; //실행인자, 파일명 여기들어갈듯
	struct s_tree_node* left_child;
	struct s_tree_node* right_child;
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
char *ft_colorstr(char *str);
char	*ft_strdup(const char *s1);

/*
** utils3.c  ++++++++3
*/
char			**ft_split(char const *s, char c);


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
void read_line(t_list *env_list, char **line);


/*
** check_syntax.c
*/
int check_syntax(char *line);

/*
** tokenize.c
*/



/*
** b_tree.c
*/
t_tree*		create_tree();
t_tree_node*	insert_root(t_tree* tree, char *command, char *argument, int flag);
t_tree_node*	insert_left(t_tree_node* parent,  char *command, char *argument, int flag);
t_tree_node*	insert_right(t_tree_node* parent, char *command, char *argument, int flag);
void	delete_tree(t_tree* tree);

void	traverseDLR(t_tree *tree); // 삭제예정
