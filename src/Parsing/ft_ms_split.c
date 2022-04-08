/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ms_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 22:30:46 by kyujlee           #+#    #+#             */
/*   Updated: 2022/04/08 08:56:02 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cnt_word(char *line, int flag, int i, int cnt)
{
	int	tmp;

	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			i = str_in_quote2(line, i);
			continue ;
		}
		tmp = is_delimiter(line[i], line[i + 1]);
		if (tmp)
		{
			cnt++;
			if (tmp == 2)
				i++;
			flag = 0;
			continue ;
		}
		else if (flag == 0 && tmp == 0)
		{
			cnt++;
			flag = 1;
		}
	}
	return (cnt);
}

static void	cut_str(char *line, char **ret)
{
	int	i;
	int	word;
	int	tmp;

	word = 0;
	i = 0;
	while (line[i])
	{
		tmp = is_delimiter(line[i], line[i + 1]);
		if (!tmp)
		{
			while (line[i + tmp] && !is_delimiter(line[i + tmp],
					line[i + tmp + 1]))
			{
				if (line[i] == '\'' || line[i] == '"')
					tmp = str_in_quote2(line, i) - i;
				tmp++;
			}
		}
		ret[word] = ft_strndup(line, i, i + tmp - 1);
		i += tmp;
		word++;
	}
}

static char	**repositioning(char **str, int flag, int i, t_info *info)
{
	char	**ret;
	char	**tmp;

	tmp = NULL;
	while (str[++i])
	{
		if (is_delimiter(str[i][0], str[i][1]))
		{
			if (i == 0 || is_delimiter(str[i - 1][0], str[i - 1][1]))
			{
				tmp = plus_space(str, i);
				divide_str(tmp, i);
			}
		}
	}
	if (tmp == NULL)
	{
		flag = 1;
		tmp = str;
	}
	ret = heredoc_processing(tmp, info);
	return (return_condition(flag, ret, tmp));
}

static void	key_to_value(t_list *env_list, char **line, int flag)
{
	int	i;
	int	tmp;

	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] == '\'')
		{
			i = str_in_quote2((*line), i);
			continue ;
		}
		if ((*line)[i] == '$')
		{
			tmp = i;
			while ((*line)[++i])
				if ((*line)[i] == ' ' || (*line)[i] == '"'
					|| (*line)[i] == '\\')
					break ;
			if (i == (int)ft_strlen(*line))
				flag = 1;
			change_str(env_list, line, tmp, i);
		}
		if (flag == 1)
			break ;
	}
}

char	**ft_ms_split(char *line, t_list *env_list, t_info *info)
{
	char	**ret;
	int		cnt;
	char	**tmp;

	info->heredoc_flag = 0;
	tmp = NULL;
	cnt = cnt_word(line, 0, -1, 0);
	ret = (char **)malloc(sizeof(char *) * (cnt + 1));
	ret[cnt] = NULL;
	key_to_value(env_list, &line, 0);
	if (cnt == 1)
		ret[0] = ft_strdup(line);
	else
		cut_str(line, ret);
	tmp = repositioning(ret, 0, -1, info);
	free(line);
	if (!tmp)
		return (ret);
	else
	{
		while (--cnt >= 0)
			free(ret[cnt]);
		free(ret);
		return (tmp);
	}
}
