#include "../minishell.h"
int read_line(t_list *env_list, char **line)
{
    char *info = ft_colorstr(get_node(env_list,
                                      get_position(env_list, "PWD"))->data);
    *line = readline(info);
    free(info);
    if (*line == NULL)
    {
        delete_list(env_list);
        exit(0);
    }
    if (*line[0] == '\0')
    {
        free(*line);
        return 0;
    }
    add_history(*line);
    return (1);
}


