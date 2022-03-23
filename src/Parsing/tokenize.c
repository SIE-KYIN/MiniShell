#include "../minishell.h"

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
    int j;

    i = 0;
    j = 0;
    if (!is_there_space(line))
        return (NULL);
    while (line[i] != ' ')
        i++;
    while (line[i + j] == ' ')
        j++;
    ret = (char **)malloc(3);
    ret[0] = ft_strndup(line, 0, i - 1);
    if ((int)ft_strlen(line) == i)
        ret[1] = NULL;
    else
        ret[1] = ft_strndup(line, i + j, ft_strlen(line) - 2);
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
    tmp = find_cmd(token[token_loc]);
    if (!deli_loc)
    {
        tmp = find_cmd(token[0]);
        insert_left(parent, tmp[0], tmp[1], COMMON_BUILTIN);
        tmp = find_cmd(token[2]);
        insert_right(parent, tmp[0], tmp[1], COMMON_BUILTIN);
        return ;
    }
    insert_right(parent, tmp[0], tmp[1], -1);
    insert_left(parent, token[deli_loc], NULL, DELIMITER);
    free(token[deli_loc]);
    token[deli_loc] = NULL;
    _token_to_tree(parent->left_child, token, token_loc - 2);
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
        insert_root(token_tree, token[deli_loc], NULL, DELIMITER);
        free(token[deli_loc]);
        token[deli_loc] = NULL;
        _token_to_tree(token_tree->root_node, token, token_loc);
    }
    else
    {
        tmp = find_cmd(token[0]);
        insert_root(token_tree, tmp[0], tmp[1], COMMON_BUILTIN);
    }
}

t_tree *tokenize(char *line)
{
    t_tree *token_tree;
    char **token;

    token_tree = create_tree();
    token = ft_ms_split(line);
    token_to_tree(token_tree, token);

    return (token_tree);
}


// int main() {
//     t_tree *pBinTree = NULL;
//     char str[] = "cat < a.txt | grep h | wc -l";
//     pBinTree = tokenize(str);
//     if (pBinTree != NULL) {
//         printf("Preorder Iterative Traversal\n");
// 		printf ("------------------------------------\n");
// 		printf ("cmd | arg | fg\n");
// 		printf ("전위순회\n");
//         pre_traverse(pBinTree);
// 		printf ("중위순회\n");
// 		in_traverse(pBinTree);
// 		printf ("후위순회\n");
// 		post_traverse(pBinTree);
//         delete_tree(pBinTree);
//     }
//     return 0;
// }

