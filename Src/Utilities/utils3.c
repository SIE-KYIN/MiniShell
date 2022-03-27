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
	int flag;

	cnt = 0;
	flag = 0;
	i = -1;
	while (line[++i])
	{
		tmp = is_delimiter(line[i],  line[i + 1]);
		if (tmp)
		{
			cnt++;
			if (tmp == 2)
				i++;
			flag = 0;
			continue;
		}
		else if (flag == 0 && tmp == 0)
		{
			cnt++;
			flag = 1;
		}
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

char *ft_emptystr()
{
	char *ret;

	ret = (char *)malloc(sizeof(char) + 1);
	if (ret == NULL)
		return NULL;
	
	ret[0] = '\0';
	
	return ret;
}

char **plus_space(char **str, int criteria)
{
	int cnt;
	char **ret;
	int i;

	cnt = strcnt_double_ptr(str);
	ret = (char **)malloc(sizeof(char *) * (cnt + 2));
	i = -1;
	while (++i < cnt)
	{
		if (i < criteria)
			ret[i] = str[i];
		else
			ret[i + 1] = str[i];
	}
	ret[cnt + 1] = NULL;
	return (ret);
}

char **divide_str(char **ret, int i)
{
	int j;
	int criteria = 0;
	int flag;
	char *tmp;
	char **str_ret;
	
	str_ret = (char **)malloc(sizeof(char *) * 3);
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
	str_ret[1] = ft_strndup(tmp, 0, criteria);
	str_ret[0] = ft_strndup(tmp, criteria + 1, j - 1);
	str_ret[2] = NULL;
	free(tmp);
	return (str_ret);
}

char **repositioning(char **str)
{
	char **ret = NULL;
	int cnt;
	int i;
	char **tmp;
	
	i = -1;
	while (str[++i])
	{
		if (is_delimiter(str[i][0], str[i][1]))
		{
			if (i == 0 || is_delimiter(str[i - 1][0], str[i -1][1]))
			{
				ret = plus_space(str, i);
				tmp = divide_str(ret, i);
				ret[i] = tmp[0];
				free(ret[i + 2]);
				ret[i + 2] = tmp[1];
				free(tmp);
			}
			
		}
	}
	return (ret);
}

char **ft_ms_split(char *line, t_list *env_list)
{
	char **ret;
	int cnt;
	char **tmp = NULL;

	cnt = cnt_word(line);
	ret = (char **)malloc(sizeof(char *) * (cnt + 1));
	ret[cnt] = NULL;
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
	strstr = ft_ms_split("ls |>test echo ho", ho);

	while (strstr[i]){
		printf ("%s\n",strstr[i]);
		i++;
	}
	system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked");
	return (0);
}


// char *ft_emptystr()
// {
// 	char *ret;

// 	ret = (char *)malloc(sizeof(char) + 1);
// 	if (ret == NULL)
// 		return NULL;
	
// 	ret[0] = '\0';
	
// 	return ret;
// }

// char *ft_strcjoin(char *str, char c){
// 	char *ret;
// 	int len;
// 	int i = -1;

// 	while (str[len])
// 		len++;

// 	ret = (char *)malloc(sizeof(char) * (len + 2));
// 	if (ret == NULL)
// 		return NULL;
	
// 	ret[len] = c;
// 	ret[len + 1] = '\0';
	
// 	while (++i < len)
// 		ret[i] = str[i];

// 	return ret;
// }

// void delete_space(char **ret)
// {
// 	char **tmp;
// 	char *tmp_str;
// 	int i;
// 	int j;

// 	i = -1;
// 	while (ret[++i])
// 	{
// 		if (is_delimiter(ret[i][0], ret[i][1]))
// 			continue;
// 		tmp = ft_split(ret[i] , ' ');
// 		free(ret[i]);
// 		ret[i] = ft_emptystr();
// 		j = 0;
// 		while (tmp[j])
// 		{
// 			tmp_str = ret[i];
// 			ret[i] = ft_strjoin(ret[i], tmp[j]);
// 			free(tmp_str);
// 			if (tmp[j + 1])
// 			{
// 				tmp_str = ret[i];
// 				ret[i] = ft_strcjoin(ret[i], ' ');
// 				free(tmp_str);
// 			}
// 			free(tmp[j]);
// 			j++;
// 		}
// 		free(tmp);
// 	}
// }