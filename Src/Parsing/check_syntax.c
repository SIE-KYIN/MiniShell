#include "../../Inc/minishell.h"

int check_quotes(char *line)
{
    int flag;

    flag = 0;
    while (*line)
    {
        if (!flag && (*line == "\"" || *line == "'")
            flag++;
        else if (flag && (*line == "\"" || *line == "'")
            flag--;
        line++;
    }
    if (flag)
        return (0);
    else
        return (1);
}

int check_special_character(char *line)
{
    int flag;

    flag = 0;
    while (*line)
    {
        if (*line == ';' && *(line + 1) == ';')
            return (0);
        if (*line == '|' && *(line + 1) == '|')
            return (0);
        line++;
    }
    return (1);
}

int check_syntax(char *line)
{
    if (!check_quotes(line))
        return (0);
    if (!check_special_character(line))
        return (0);
    return (1);
}