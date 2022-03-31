int is_delimiter(char c, char next)
{
    if (c == '>')
    {
        if (next == '>')
            return (2);
        return(1);
    }
    if (c == '<')
    {
        if (next == '<')
            return (2);
        return(1);
    }
    if (c == '|')
        return (1);
    return (0);
}
int cnt_delimiter(char *line)
{
    int ret;
    int tmp;
    ret = 0;
    while (*line)
    {
        tmp = is_delimiter(*line,  *(line + 1));
        if (tmp)
        {
            line += tmp;
            ret++;
        }
        else
            line++;
    }
    return (ret);
}
int cnt_word(char *line)
{
    int i;
    int cnt;
    int tmp;
    cnt = 0;
    while (*line)
    {
        tmp = is_delimiter(*line,  *(line + 1));
        if (tmp)
        {
            cnt++;
            line += tmp;
            continue;
        }
        cnt++;
        while (!is_delimiter(*line, *(line + 1)) && *line)
            line++;
    }
    return (cnt);
}
void cut_str(char *line, char **ret)
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
int strcnt_double_ptr(char **ret)
{
    int i;
    i = 0;
    while (ret[i])
        i++;
    return (i);
}
char **plus_space(char **str, int criteria)
{
    int cnt;
    char **ret;
    int i;
    cnt = strcnt_double_ptr(str);
    ret = (char **)malloc(cnt + 2);
    i = -1;
    while (++i < cnt)
    {
        if (i < criteria)
            ret[i] = str[i];
        else
            ret[i + 1] = str[i];
    }
    ret[cnt + 1] = 0;
    return (ret);
}

void divide_str(char **ret, int i)
{
    char *command = NULL;
    char *argument = NULL;
    int j;
    int criteria = 0;
    int flag;
    char *tmp;
    tmp = ft_strdup(ret[i + 2]);
    flag = 0;
    j = -1;
    while (tmp[++j])
    {
        if (flag == 1 && tmp[j] == ' ')
        {
            criteria = j;
            flag++;
        }
        if (!flag && tmp[j] != ' ')
            flag = 1;
    }
    argument = ft_strndup(tmp, 0, criteria);
    command = ft_strndup(tmp, criteria + 1, j - 1);
    ret[i] = command;
    // free(ret[i + 2]);
    ret[i + 2] = argument;
    // free(tmp);
}
char **repositioning(char **str)
{
    char **ret = NULL;
    int cnt;
    int i;
    i = -1;
    while (str[++i])
    {
        if (is_delimiter(str[i][0], str[i][1]))
        {
            if (i == 0 || is_delimiter(str[i - 1][0], str[i -1][1]))
            {
                ret = plus_space(str, i);
                divide_str(ret, i);
            }
        }
    }
    return (ret);
}
char **ft_ms_split(char *line, t_list *env_list)
{
    char **ret;
    int cnt;
    char **tmp;
    cnt = cnt_word(line);
    ret = (char **)malloc(sizeof(char *) * (cnt + 1));
    ret[cnt] = 0;
    if (cnt == 1)
        ret[0] = ft_strdup(line);
    else
        cut_str(line, ret);
    tmp = repositioning(ret);
    if (!tmp)
    // key_to_value(env_list, ret);
        return (ret);
    else
    {
        free(ret);
        return (tmp);
    }
}
int main(int argc, char **argv, char **envv)
{
    char **strstr;
    t_list *ho;
	ho = NULL;
    // ho = parse_envv(envv);
    int i=0;
    strstr = ft_ms_split("> test echo ho", ho);
    while (strstr[i]){
        printf ("%s\n",strstr[i]);
        i++;
    }
    system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked");
    return (0);
}