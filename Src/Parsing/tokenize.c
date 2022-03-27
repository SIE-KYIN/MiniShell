#include "../../Inc/minishell.h"

int is_there_space(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == ' ')
            return (1);
        i++;
    }
    return (0);
}

char **find_cmd(char *line)
{
    char **ret;
    int i;
    int flag;

    flag = 0;
    i = -1;
    while (line[++i])
        if (line[i] == 'e' && line[i + 1] == 'c' && line[i + 2] == 'h' && line[i + 3] == 'o' && line[i + 4] == ' ')
        {
            flag = 1;
            break;
        }
    if (flag == 1)
    {
        ret = (char **)malloc(sizeof(char *) * 3);
        ret[0] = ft_strndup(line, i, i + 3);
        i += 3;
        while (line[++i])
            if (line[i] != ' ')
                break;
        ret[1] = ft_strndup(line, i, ft_strlen(line) - 1);
        ret[2] = 0;
    }
    else
        ret = ft_split(line, ' ');
    free(line);
    return (ret);
}


int token_cnt(char **token)
{
    int ret;
    int i;

    i = 0;
    ret = 0;
    while (token[i])
    {
        ret++;
        i++;    
    }
    return (ret);
}

int is_there_delimiter(char **token)
{
    int cnt;

    cnt = token_cnt(token);
    while (cnt--)
        if (is_delimiter(token[cnt][0], token[cnt][1]))
            return (cnt);
    return (0);
}

int get_latest_token_loc(char **token)
{
    int i;
    
    i = 0;
    while (token[i + 1])
        i++;
    return (i);
}

void _token_to_tree(t_tree_node *parent, char **token, int token_loc)
{
    char **tmp;
    int deli_loc;

    deli_loc = is_there_delimiter(token);
    // token_loc = get_latest_token_loc(token);
    if (!deli_loc)
    {
        tmp = find_cmd(token[0]);
        insert_left(parent, tmp, COMMON_BUILTIN);
        tmp = find_cmd(token[2]);
        insert_right(parent, tmp, COMMON_BUILTIN);
        return ;
    }
    tmp = find_cmd(token[token_loc]);
    insert_right(parent, tmp, -1);
    tmp = (char **)malloc(sizeof(char *) * 2);
    tmp[0] = ft_strdup(token[deli_loc]);
    tmp[1] = 0;
    insert_left(parent, tmp, DELIMITER);
    free(token[deli_loc]);
    token[deli_loc] = NULL;
    _token_to_tree(parent->left, token, token_loc - 2);
}

void token_to_tree(t_tree *token_tree, char **token)
{
    int deli_loc;
    int token_loc;
    char **tmp;

    deli_loc = is_there_delimiter(token);
    token_loc = get_latest_token_loc(token);
    if (deli_loc)
    {
        tmp = (char **)malloc(sizeof(char *) * 2);
        tmp[0] = ft_strdup(token[deli_loc]);
        tmp[1] = 0;
        insert_root(token_tree, tmp, DELIMITER);
        free(token[deli_loc]);
        token[deli_loc] = NULL;
        _token_to_tree(token_tree->root_node, token, token_loc);
    }
    else
    {
        tmp = find_cmd(token[0]);
        insert_root(token_tree, tmp, COMMON_BUILTIN);
    }
}

t_tree *tokenize(char *line, t_list *env_list)
{
    t_tree *token_tree;
    char **token;

    token_tree = create_tree();
    token = ft_ms_split(line, env_list);
    token_to_tree(token_tree, token);
    free(token);
    pre_traverse(token_tree);
    return (token_tree);
}


int main(int argc, char **argv, char **envv) {
    t_tree *pBinTree = NULL;
    char *str;
    	t_list *ho;
	ho = parse_envv(envv);
    str = ft_strdup("ls |> test echo ho");
    pBinTree = tokenize(str, ho);
    
    // if (pBinTree != NULL) {
    //     printf("Preorder Iterative Traversal\n");
	// 	printf ("....------------------------------------\n");
		// // printf ("cmd | fg\n");
		// printf ("\n\n\n전위순회\n");
        // pre_traverse(pBinTree);
	// 	printf ("중위순회\n");
	// 	in_traverse(pBinTree);
	// 	printf ("후위순회\n");
	// 	post_traverse(pBinTree);
    //     delete_tree(pBinTree);
    // }
    system("leaks token > leaks_result_temp; cat leaks_result_temp | grep leaked");
    return 0;
}
