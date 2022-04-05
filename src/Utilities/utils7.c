#include "../minishell.h"

static size_t	cnt_word(char *s, char c)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (*(s + i))
	{
		if (*(s + i) == c)
			i++;
		else
		{
			if (*(s + i) == '"' || *(s + i) == '\'')
			{
				if (i == 0 || *(s + i - 1) == ' ')
					cnt++;
				i = str_in_quote2(s, i) + 1;
				continue;
			}
			else
			{
				if (i == 0 || *(s + i - 1) == ' ')
					cnt++;;
				while (*(s + i) != c && *(s + i) && *(s + i) != '"' && *(s + i) != '\'')
					i++;
			}
		}
	}
	return (cnt);
}


static int		cut_str(char *s, char c, char **ret, size_t word)
{
	size_t	idx1;
	size_t	idx2;

	idx1 = 0;
	while (*(s + idx1))
	{
		if (*(s + idx1) == c)
			idx1++;
		else
		{
			idx2 = 0;
			while (*(s + idx1 + idx2) != c && *(s + idx1 + idx2))
			{
				if (*(s + idx1 + idx2) == '"' || *(s + idx1 + idx2) == '\'')
					idx2 = str_in_quote2(s, idx1 + idx2) - idx1;
				idx2++;
			}
			*(ret + word) = (char *)malloc(idx2 + 1);
			ft_memcpy(*(ret + word), s + idx1, idx2);
			*(*(ret + word) + idx2) = 0;
			idx1 += idx2;
			word++;
		}
	}
	return (1);
}

char			**ft_cmd_split(char *s, char c)
{
	size_t	cnt;
	char	**ret;

	if (!s)
		return ((void *)0);
	cnt = cnt_word(s, c);
	ret = (char **)malloc(sizeof(char *) * (cnt + 1));
	*(ret + cnt) = 0;
	if (!cut_str(s, c, ret, 0))
		return (0);
	return (ret);
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

void set_value(char **dup_str, bool *flag, int *j)
{
    *dup_str = ft_emptystr();
    *flag = false;
    *j = -1;
}