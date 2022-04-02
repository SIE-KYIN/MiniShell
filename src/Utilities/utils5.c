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
    i = -1;
    int flag;

    flag = 0;
    while (line[++(i)])
    {
        if (line[i] == 'e' && line[i + 1] == 'c' && line[i + 2] == 'h' && line[i + 3] == 'o' &&
            (line[i + 4] == ' ' || line[i + 4] == '"' || line[i + 4] == '\''))
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

int cnt_echo_str(char *line)
{
    int ret;
    int i;
    int j;

    i = -1;
    ret = 0;
    while (line[++i])
    {
        while (line[i] == ' ')
            i++;
        if (line[i] == '\'' || line[i] == '"')
		{
			i = str_in_quote2(line, i);
            ret++;
			continue;
		}
        else
        {
            j = 0;
            while (line[i + 1] && (line[i + 1] != ' ' && line[i + 1] != '\'' && line[i + 1] != '"'))
                i++;
            ret++;
        }
    }
    return (ret);
}

void cut_echo_str(char **ret, char *line, int word_i)
{
    int i;
    int tmp;

    i = -1;
    while (line[++i])
    {
        while (line[i] == ' ')
            i++;
        if (line[i] == '\'' || line[i] == '"')
		{
			tmp = str_in_quote2(line, i);
            ret[word_i++] = ft_strndup(line, i + 1, tmp - 1);
            i = tmp;
			continue;
		}
        else
        {
            tmp = 0;
            while (line[i + tmp + 1] && (line[i + tmp + 1] != ' ' && line[i + tmp + 1] != '\'' && line[i + tmp + 1] != '"'))
                tmp++;
            ret[word_i++] = ft_strndup(line, i, i + tmp);
            i += tmp;
        }
    }
}


char **find_cmd(char *line,int flag)
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

int is_there_delimiter(char **token, int token_cnt)
{
    int cnt;

    cnt = -1;
    while (++cnt < token_cnt)
	{
		if (token[cnt] == NULL)
			continue;
        if (is_delimiter(token[cnt][0], token[cnt][1]))
            return (cnt);
	}
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