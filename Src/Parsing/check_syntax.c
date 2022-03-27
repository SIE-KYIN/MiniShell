#include "../../Inc/minishell.h"

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
                if (line[i + 2] == line[i])
                    return (0);
            if (line[i] == '$' || line[i] == '|' || line[i] == '$')
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
        else if (line[i] == '|' || line[i] == '$'
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
        free(line);
        return (0);
    }
    if (!is_valid_location(line))
    {
        ft_error(3);
        free(line);
        return (0);
    }
    if (!is_opened_quotes(line))
    {
        ft_error(4);
        free(line);
        return (0);
    }
    return (1);
}

//오픈 따옴표일때 (\"는 예외처리해야함)
// > < 로 시작하거나 끝나는 것
// 따옴표안에 없는 특수기호 | , $ 제외
// 허용된 특수기호 개수체크 