#include "../../Inc/minishell.h"

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
int main(){
	printf ("%d", cnt_word("cd .. | ls | cat minishell.c > a.txt | df"));
}

// char **ft_ms_split(char *line)
// {
// 	char **ret;
// 	int cnt;

// 	cnt = cnt_word(line);
// 	if (cnt == 1)
// 		return (NULL);
// 	ret = (char **)malloc(sizeof(char *) * (cnt + 1));
// 	ret[cnt] = '\0';
// 	cut_str(line, ret)
// 	return (ret);
// }