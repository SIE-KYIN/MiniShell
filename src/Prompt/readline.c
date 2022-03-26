#include "../minishell.h"

void parse_line(t_tree *tree, char **env)
{
    char **arg;
    int backup_std[2];

	(void)env;
	(void)arg;

    backup_std[0] = dup(0);
    backup_std[1] = dup(1);

	pre_traverse(tree, env);
}

// void gshim_read_line(t_list *env_list, char *line, char **envv)
// {

//     char *info = ft_colorstr(get_node(env_list, get_position(env_list, "PWD"))->data);
//     line = readline(info);
//     free(info);
//     if (line == NULL)
//         exit(0);

//     //printf("%s\n", line);
//     parse_line(line, envv);

//     add_history(line);
//     free(line);
//     line = NULL;
// }

void read_line(t_list *env_list, char **line)
{

    char *info = ft_colorstr(get_node(env_list,
                                      get_position(env_list, "PWD"))->data);
    *line = readline(info);
    free(info);
    if (*line == NULL)
        exit(0);
    add_history(*line);
    // free(line);

    // *line = NULL;
}
