#include "../minishell.h"

//
static int cnt_word(char *line, int flag)
{
	int i;
	int cnt;
	int tmp;

	cnt = 0;
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

static void cut_str(char *line, char **ret)
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

static char **repositioning(char **str)
{
	char **ret = NULL;
	int i;

	i = -1;
	while (str[++i])
	{
		if (is_delimiter(str[i][0], str[i][1]))
		{
			if (i == 0 || is_delimiter(str[i - 1][0], str[i -1][1]))
			{
				ret = plus_space(str, i);
				divide_str(ret, i);
			}
		}
	}
	return (ret);
}


static void key_to_value(t_list *env_list, char **line, int flag)
{
	int i;
	int tmp;

	i = 0;
	while ((*line)[++i])
	{
		if ((*line)[i] == '\'')
		{
			i = str_in_quote2((*line), i);
			continue;
		}
		if ((*line)[i] == '$')
		{
			tmp = i;
			while((*line)[++i])
				if ((*line)[i] == ' ' || (*line)[i] == '"' || (*line)[i] == '\\')
					break;
			if (i == (int)ft_strlen(*line))
				flag = 1;
			change_str(env_list, line, tmp, i);
		}
		if (flag == 1)
			break;
	}
}

char **ft_ms_split(char *line, t_list *env_list)
{
	char **ret;
	int cnt;
	char **tmp;

	tmp = NULL;
	cnt = cnt_word(line, 0);
	ret = (char **)malloc(sizeof(char *) * (cnt + 1));
	ret[cnt] = NULL;
	key_to_value(env_list, &line, 0);
	if (cnt == 1)
		ret[0] = ft_strdup(line); // ">ls "를 입력하면..?
	else
		cut_str(line, ret);
	tmp = repositioning(ret);//????
	free(line);
	if (!tmp)
		return (ret);
	else
	{
		cnt = -1;
		while (ret[++cnt])
			free(ret[cnt]);
		free(ret);
		return (tmp);
	}
}

// int main(int argc, char **argv, char **envv)
// {
// 	char **strstr;
// 	char *tmp;
// 	t_list *ho;
// 	ho = parse_envv(envv);
// 	tmp = ft_strdup("ls |>test echo ho");
// 	int i=0;
// 	strstr = ft_ms_split(tmp, ho);

// 	while (strstr[i]){
// 		printf ("%s\n",strstr[i]);
// 		i++;
// 	}
// 	system("leaks token > leaks_result_temp; cat leaks_result_temp | grep leaked");
// 	return (0);
// }


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
