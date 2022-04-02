#include "../minishell.h"

t_list *parse_envv(char **envv)
{
    t_list *list;
    char *var;
    char *data;
    int i;
    int j;
    int tmp;

    i = -1;
    list = create_list();
	list->top.data = ft_strdup("0");
	list->top.var = ft_strdup("?");
    while (envv[++i])
    {
        j = -1;
        while (envv[i][++j])
            if (envv[i][j + 1] == '=')
                tmp = j;
        var = ft_strndup(envv[i], 0, tmp);
        data = ft_strndup(envv[i], tmp + 2, j - 1);
        add_node(list, i, var, data);
    }
    return (list);
}

// list -> char **
char **gather(t_list *list)
{
	char **ret;
	int i;
	t_list_node *node;

	ret = malloc(sizeof(char *) * (list->cnt + 1));
	i = 0;
	node = list->top.next;
	// 모든 리스트노드에 접근
	while(i < list->cnt)
	{
		char *var = ft_strdup(node->var);
		char *data = ft_strdup(node->data);
		ret[i] = ft_strjoin_3(var, "=", data);
		free(var);
		free(data);
		node = node->next;
		i++;
	}
	ret[i] = NULL;

	// [DEBUG] 왜 파란색으로 나오지...?
	// for(int i=0;i<list->cnt;i++)
	// {
	// 	printf("%s\n", ret[i]);
	// }

	return ret;
}
