#include "../../Inc/minishell.h"

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