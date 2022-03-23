#include "../minishell.h"

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

char *ft_emptystr()
{
	char *ret;

	ret = (char *)malloc(sizeof(char) + 1);
	if (ret == NULL)
		return NULL;

	ret[0] = '\0';

	return ret;
}

char *ft_strcjoin(char *str, char c){
	char *ret;
	int len;
	int i = -1;

	len = 0;
	while (str[len])
		len++;

	ret = (char *)malloc(sizeof(char) * (len + 2));
	if (ret == NULL)
		return NULL;

	ret[len] = c;
	ret[len + 1] = '\0';

	while (++i < len)
		ret[i] = str[i];

	return ret;
}

void delete_space(char **ret)
{
	char **tmp;
	char *tmp_str;
	int i;
	int j;

	i = -1;
	while (ret[++i])
	{
		if (is_delimiter(ret[i][0], ret[i][1]))
			continue;
		tmp = ft_split(ret[i] , ' ');
		free(ret[i]);
		ret[i] = ft_emptystr();
		j = 0;
		while (tmp[j])
		{
			tmp_str = ret[i];
			ret[i] = ft_strjoin(ret[i], tmp[j]);
			free(tmp_str);
			if (tmp[j + 1])
			{
				tmp_str = ret[i];
				ret[i] = ft_strcjoin(ret[i], ' ');
				free(tmp_str);
			}
			free(tmp[j]);
			j++;
		}
		free(tmp);
	}
}

char **ft_ms_split(char *line)
{
	char **ret;
	int cnt;

	cnt = cnt_word(line);
	ret = (char **)malloc(sizeof(char *) * (cnt + 1));
	ret[cnt] = 0;
	if (cnt == 1)
		ret[0] = ft_strdup(line);
	else
		cut_str(line, ret);
	// delete_space(ret);
	return (ret);
}

// int main(){
// 	char **ret;
// 	int i=0;
// 	ret =ft_ms_split("echo \"abc\"\'ccc    \'\"d    acc    \">a>b");
// 	while (ret[i]){
// 		printf ("%s\n",ret[i]);
// 		i++;
// 	}
// }