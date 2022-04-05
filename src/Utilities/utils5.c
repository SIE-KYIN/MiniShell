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

int is_echo(char *line)
{
    int i;
    int flag;
    
    i = -1;
    flag = 0;
    while (line[++i])
    {
        if (line[i] == 'e' && line[i + 1] == 'c' && line[i + 2] == 'h' && line[i + 3] == 'o' && 
            (line[i + 4] == ' ' || line[i + 4] == '"' || line[i + 4] == '\'' || line[i + 4] == '\0'))
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
        return (1);
    else
        return (0);
}

int str_in_quote2(char *line, int i)
{
    char curr_quote;
    
    curr_quote = line[i];
    while(line[++i])
    {
        if (line[i - 1] != '\\' && curr_quote == line[i])
            break;
    }
    return (i);
}

void delete_quotes(char **ret)
{
    int i;
    int j;
    int from;
    int to;
    char *dup_str;
    char *tmp;
    char *free_tmp;

    i = -1;
    while (ret[++i])
    {
        dup_str = ft_emptystr();
        j = -1;
        while (ret[i][++j])
        {
            if (ret[i][j] == '"' || ret[i][j] == '\'')
            {
                from = j + 1;
                to = str_in_quote2(ret[i] , j);
                tmp = ft_strndup(ret[i], from, to - 1);
            }
            else
            {
                from = j;
                to = j;
                while (ret[i][to + 1] && ret[i][to + 1] != '"' && ret[i][to + 1] != '\'')
                    to++;
                tmp = ft_strndup(ret[i], from, to);
            }
            free_tmp = dup_str;
            dup_str = ft_strjoin(free_tmp, tmp);
            free(tmp);
            free(free_tmp);
            j = to;
        }
        free_tmp = ret[i];
        ret[i] = dup_str;
        free(free_tmp);
    }

}

char *str_delete(char *str, int curr, bool flag)
{
    char *ret;
    char *tmp;
    char *free_tmp;
    int cnt;
    int i;

    i = curr - 1;
    cnt =0;
    free_tmp = ft_strndup(str, 0, curr - 1);
    while (str[++i] == '\\')
        cnt++;
    i = -1;
    if (flag == true)
        i = cnt / 2;
    else
        i = (cnt + 1) / 2;
    while (--i >= 0)
            curr++;
    tmp = ft_strndup(str, curr, ft_strlen(str));
    ret = ft_strjoin(free_tmp, tmp);
    free(free_tmp);
    free(tmp);
    return (ret);
}

void delete_slash(char **ret)
{
    int i;
    int j;
    bool flag;
    char *dup_str;
    char *free_tmp;

    i = -1;
    while (ret[++i])
    {
        dup_str = ft_emptystr();
        flag = false;
        j = -1;
        while (ret[i][++j])
        {
            if (ret[i][j] == '\'' || ret[i][j] == '"')
                flag = !flag;
            if (ret[i][j] == '\\')
            {
                free_tmp = dup_str;
                dup_str = str_delete(ret[i], j, flag);
                free(free_tmp);
                while (ret[i][j] == '\\')
                    j++;
            }
        }
        if (dup_str[0] != '\0')
        {
            free_tmp = ret[i];
            ret[i] = ft_strdup(dup_str);
            free(free_tmp);
        }
        free(dup_str);
    }
}

char **find_cmd(char *line)
{
    char **ret;

    ret = ft_cmd_split(line, ' ');
    delete_slash(ret);
    delete_quotes(ret);
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