/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 23:00:00 by kyujlee           #+#    #+#             */
/*   Updated: 2022/04/08 01:25:48 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_str_except_quote(char *str, int j, int *to)
{
	char	*ret;
	int		from;

	if (str[j] == '"' || str[j] == '\'')
	{
		from = j + 1;
		*to = str_in_quote2(str, j);
		ret = ft_strndup(str, from, *to - 1);
	}
	else
	{
		from = j;
		*to = j;
		while (str[*to + 1] && str[*to + 1] != '"' && str[*to + 1] != '\'')
			(*to)++;
		ret = ft_strndup(str, from, *to);
	}
	return (ret);
}

void	delete_quotes(char **ret, char *free_tmp)
{
	int		i;
	int		j;
	int		to;
	char	*dup_str;
	char	*tmp;

	i = -1;
	while (ret[++i])
	{
		dup_str = ft_emptystr();
		j = -1;
		while (ret[i][++j])
		{
			tmp = get_str_except_quote(ret[i], j, &to);
			free_tmp = dup_str;
			dup_str = ft_strjoin(free_tmp, tmp);
			free(tmp);
			free(free_tmp);
			j = to;
		}
		free_tmp = ret[i];
		ret[i] = dup_str;
		free(free_tmp);
	}
}

char	*str_delete(char *str, int curr, bool flag)
{
	char	*ret;
	char	*tmp;
	char	*free_tmp;
	int		cnt;
	int		i;

	i = curr - 1;
	cnt = 0;
	free_tmp = ft_strndup(str, 0, curr - 1);
	while (str[++i] == '\\')
		cnt++;
	i = -1;
	if (flag == true)
		i = cnt / 2;
	else
		i = (cnt + 1) / 2;
	while (--i >= 0)
		curr++;
	tmp = ft_strndup(str, curr, ft_strlen(str));
	ret = ft_strjoin(free_tmp, tmp);
	free(free_tmp);
	free(tmp);
	return (ret);
}

void	check_only(char **ret, char *dup_str, int i)
{
	char	*free_tmp;

	if (dup_str[0] != '\0')
	{
		free_tmp = ret[i];
		ret[i] = ft_strdup(dup_str);
		free(free_tmp);
	}
}

void	delete_slash(char **ret, int i, bool flag, char *free_tmp)
{
	int		j;
	char	*dup_str;

	while (ret[++i])
	{
		set_value(&dup_str, &flag, &j);
		while (ret[i][++j])
		{
			if (ret[i][j] == '\'' || ret[i][j] == '"')
				flag = !flag;
			if (ret[i][j] == '\\')
			{
				free_tmp = dup_str;
				dup_str = str_delete(ret[i], j, flag);
				free(free_tmp);
				while (ret[i][j] == '\\')
					j++;
			}
		}
		check_only(ret, dup_str, i);
		free(dup_str);
	}
}
