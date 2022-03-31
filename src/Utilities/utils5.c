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

char **find_cmd(char *line, int flag)
{
    char **ret;
    int i;

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