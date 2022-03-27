#include "../../Inc/minishell.h"

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
    if (33 <= c && c <= 47
            || 58 <= c && c <= 64
            || 91 <= c && c <= 96
            || 123 <= c && c <= 126)
                if (c != '|' && c != '<' 
                    && c != '>' && c != '$'
                    && c != '"' && c != '\''
                    && c != '?' && c != '.')
                         return (0);
    return (1);
}