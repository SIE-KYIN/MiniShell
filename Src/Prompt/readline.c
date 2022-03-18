#include "../../Inc/minishell.h"

void read_line(t_list *env_list, char *line)
{
    
    char *info = ft_colorstr(get_node(env_list, 
                                      get_position(env_list, "PWD"))->data);
    line = readline(info);
    free(info);
    if (line == NULL)
        exit(0);
    printf("%s\n", line);
    add_history(line);
    // free(line);
    line = NULL;
}
