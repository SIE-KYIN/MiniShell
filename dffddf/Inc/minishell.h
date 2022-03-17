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
void read_line(t_list *env_list, char *line);
