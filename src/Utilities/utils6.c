#include "../minishell.h"

static size_t	cnt_word(char const *s, char c)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (*(s + i))
	{
		if (*(s + i) == c || *(s + i) == '\'' || *(s + i) == '"')
			i++;
		else
		{
			cnt++;
			while (*(s + i) != c && *(s + i))
				i++;
		}
	}
	return (cnt);
}

static int		cut_str(char const *s, char c, char **ret, size_t word)
{
	size_t	idx1;
	size_t	idx2;
    int tmp;

	idx1 = 0;
	while (*(s + idx1))
	{
		if (*(s + idx1) == c || *(s + idx1) == '"' || *(s + idx1) == '\'')
			idx1++;
		else
		{
			idx2 = 0;
            tmp = 0;
			while (*(s + idx1 + idx2) != c && *(s + idx1 + idx2))
            {
                if (*(s + idx1 + idx2) == '"' || *(s + idx1 + idx2) == '\'')
                    tmp++;
				idx2++;
            }
			*(ret + word) = (char *)malloc(idx2 - tmp + 1);
			ft_memcpy(*(ret + word), s + idx1, idx2 - tmp);
			*(*(ret + word) + idx2 - tmp) = 0;
			idx1 += idx2;
			word++;
		}
	}
	return (1);
}

char			**split_delete_quotes(char const *s, char c)
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