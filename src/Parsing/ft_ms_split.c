#include "../minishell.h"

static int cnt_word(char *line, int flag)
{
    int i;
    int cnt;
    int tmp;
    cnt = 0;
    i = -1;
    while (line[++i])
    {
        tmp = is_delimiter(line[i],  line[i + 1]);
        if (tmp)
        {
            cnt++;
            if (tmp == 2)
                i++;
            flag = 0;
            continue;
        }
        else if (flag == 0 && tmp == 0)
        {
            cnt++;
            flag = 1;
        }
    }
    return (cnt);
}
static void cut_str(char *line, char **ret)
{
    int i;
    int word;
    int tmp;
    word = 0;
    i = 0;
    while (line[i])
    {
        tmp = is_delimiter(line[i],  line[i + 1]);
        if (!tmp)
            while (line[i + tmp] && !is_delimiter(line[i + tmp],  line[i + tmp + 1]))
                tmp++;
        ret[word] = ft_strndup(line, i, i + tmp - 1);
        i += tmp;
        word++;
    }
}
char **heredoc_processing(char **str)
{
    int i;
    int heredoc_cnt;
    char **heredoc_str;
    char **ret;
    int cnt;
    i = -1;
    heredoc_cnt = 0;
    while (str[++i])
        if (str[i][0] == '<' && str[i][1] == '<')
            heredoc_cnt += 2;
    if (heredoc_cnt == 0)
        return (NULL);
    cnt = strcnt_double_ptr(str);
    heredoc_str = (char **)malloc(sizeof(char *) * (heredoc_cnt + 1));
    ret= (char **)malloc(sizeof(char *) * (cnt + 1));
    heredoc_str[heredoc_cnt--] = NULL;
    ret[cnt] = NULL;
    i = -1;
    cnt = 0;
    while (str[++i])
    {
        if (str[i][0] == '<' && str[i][1] == '<')
        {
            heredoc_str[heredoc_cnt--] =  str[i + 1];
            heredoc_str[heredoc_cnt--] = str[i++];
        }
        else
            ret[cnt++] = ft_strdup(str[i]);
    }
    i = -1;
    while (heredoc_str[++i])
        ret[cnt++] = ft_strdup(heredoc_str[i]);
    free(heredoc_str);
    return (ret);
}
static char **repositioning(char **str)
{
    char **ret;
    char **tmp;
    int i;
    int flag;
    flag = 0;
    i = -1;
    tmp = NULL;
    while (str[++i])
    {
        if (is_delimiter(str[i][0], str[i][1]))
        {
            if (i == 0 || is_delimiter(str[i - 1][0], str[i -1][1]))
            {
                tmp = plus_space(str, i);
                divide_str(tmp, i);
            }
        }
    }
    if (tmp == NULL)
    {
        flag = 1;
        tmp = str;
    }
    ret = heredoc_processing(tmp);
    if (flag == 0 && ret == NULL)
        return (tmp);
    else if (flag == 1 && ret == NULL)
        return (NULL);
    return (ret);
}
static void key_to_value(t_list *env_list, char **line, int flag)
{
    int i;
    int tmp;
    i = 0;
    while ((*line)[++i])
    {
        if ((*line)[i] == '\'')
        {
            i = str_in_quote2((*line), i);
            continue;
        }
        if ((*line)[i] == '$')
        {
            tmp = i;
            while((*line)[++i])
                if ((*line)[i] == ' ' || (*line)[i] == '"' || (*line)[i] == '\\')
                    break;
            if (i == (int)ft_strlen(*line))
                flag = 1;
            change_str(env_list, line, tmp, i);
        }
        if (flag == 1)
            break;
    }
}
char **ft_ms_split(char *line, t_list *env_list)
{
    char **ret;
    int cnt;
    char **tmp;
    tmp = NULL;
    cnt = cnt_word(line, 0);
    ret = (char **)malloc(sizeof(char *) * (cnt + 1));
    ret[cnt] = NULL;
    key_to_value(env_list, &line, 0);
    if (cnt == 1)
        ret[0] = ft_strdup(line);
    else
        cut_str(line, ret);
    tmp = repositioning(ret);
    free(line);
    if (!tmp)
        return (ret);
    else
    {
        cnt = -1;
        while (ret[++cnt])
            free(ret[cnt]);
        free(ret);
        return (tmp);
    }
}