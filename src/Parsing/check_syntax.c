#include "../minishell.h"

int str_in_quote(char *line, int i, int *single_flag, int *double_flag)
{
    int tmp1;
    int tmp2;

    tmp1 = *single_flag + 2;
    tmp2 = *double_flag + 2;
    while (tmp1 != *single_flag && tmp2 != *double_flag && line[++i])
    {
        if (*single_flag == tmp1 - 2 && line[i] == '"')
        {
            if (line[i - 1] == '\\')
                continue;
            (*double_flag)++;
        }
        else if (*double_flag == tmp2 - 2 && line[i] == '\'')
        {
            if (line[i - 1] == '\\')
                continue;
            (*single_flag)++;
        }
    }
    return (i);
}

int str_in_quote2(char *line, int i, int single_flag, int double_flag)
{
    int tmp1;
    int tmp2;

    tmp1 = 2;
    tmp2 = 2;
    while (tmp1 != single_flag && tmp2 != double_flag && line[++i])
    {
        if (single_flag == tmp1 - 2 && line[i] == '"')
        {
            if (line[i - 1] == '\\')
                continue;
            (double_flag)++;
        }
        else if (double_flag == tmp2 - 2 && line[i] == '\'')
        {
            if (line[i - 1] == '\\')
                continue;
            (single_flag)++;
        }
    }
    return (i);
}

int is_valid_s_c(char c)
{
    if ((33 <= c && c <= 47)
            || (58 <= c && c <= 64)
            || (91 <= c && c <= 96)
            || (123 <= c && c <= 126))
                if ((c != '|' && c != '<')
                    && (c != '>' && c != '$')
                    && (c != '"' && c != '\'')
                    && (c != '?' && c != '.'))
                         return (0);
    return (1);
}

int is_valid_special_character(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (!is_valid_s_c(line[i]))
            return (0);
        if (line[i] == '?' && line[i - 1] != '$')
                return (0);
        if (is_valid_s_c(line[i]) && (line[i] != '\'' && line[i] != '"'))
        {
            if (line[i] == '<' || line[i] == '>' || line[i] == '.')
            {
                if (line[i + 2] == line[i])
                    return (0);
            }
            else if (line[i] == '$' || line[i] == '|' || line[i] == '$')
                if (line[i + 1] == line[i])
                    return (0);
        }
        if (line[i + 1] == '"' || line[i + 1] == '\'')
            i = str_in_quote2(line, i, 0, 0);
        else
            i++;
    }
    return (1);
}

int is_opened_quotes(char *line)
{
    int single_flag;
    int double_flag;
    int i;

    single_flag = 0;
    double_flag = 0;
    i = 0;

    while (line[i])
    {
        if (line[i + 1] == '"' || line[i + 1] == '\'')
            i = str_in_quote(line, i, &single_flag, &double_flag);
        else
            i++;
    }
    if (single_flag % 2 || double_flag % 2)
        return (0);
    return (1);
}

int is_valid_location(char *line)
{
    int i;

    i = -1;
    while (line[++i])
    {
        if (line[i] == ' ')
            continue;
        else if (line[i] == '>' || line[i] == '<'
                || line[i] == '|' || line[i] == '$'
                || line[i] == '\'' || line[i] == '"')
            return (0);
        else
            break;
    }
    i = ft_strlen(line);
    while (line[--i])
    {
        if (line[i] == ' ')
            continue;
        else if (line[i] == '>' || line[i] == '<'
                || line[i] == '|' || line[i] == '$')
            return (0);
        else
            break;
    }
    return (1);
}



int check_syntax(char *line)
{
    if (!is_valid_special_character(line))
    {
        ft_error(2);
        return (0);
    }
    if (!is_valid_location(line))
    {
        ft_error(3);
        return (0);
    }
    if (!is_opened_quotes(line))
    {
        ft_error(4);
        return (0);
    }
    return (1);
}

//오픈 따옴표일때 (\"는 예외처리해야함)
// > < 로 시작하거나 끝나는 것
// 따옴표안에 없는 특수기호 | , $ 제외
// 허용된 특수기호 개수체크