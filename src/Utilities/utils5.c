/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 23:01:00 by kyujlee           #+#    #+#             */
/*   Updated: 2022/04/07 17:55:14 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	divide_d_ptr(char **str, char **hd_str, char **ret, int heredoc_cnt)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i][0] == '<' && str[i][1] == '<')
		{
			hd_str[heredoc_cnt--] = str[i + 1];
			hd_str[heredoc_cnt--] = str[i++];
		}
		else
			ret[cnt++] = ft_strdup(str[i]);
	}
}

char    **heredoc_processing(char **str)
{
	int     i;
	int     heredoc_cnt;
	char    **heredoc_str;
	char    **ret;
	int     cnt;

	i = -1;
	heredoc_cnt = 0;
	while (str[++i])
		if (str[i][0] == '<' && str[i][1] == '<')
			heredoc_cnt += 2;
	if (heredoc_cnt == 0 || heredoc_cnt == 2
		|| (heredoc_cnt == 4 && !(str[1][0] == '<' && str[3][0] == '<')))
		return (NULL);
	cnt = strcnt_double_ptr(str);
	heredoc_str = (char **)malloc(sizeof(char *) * (heredoc_cnt + 1));
	ret = (char **)malloc(sizeof(char *) * (cnt + 1));
	heredoc_str[heredoc_cnt--] = NULL;
	ret[cnt] = NULL;
	divide_d_ptr(str, heredoc_str, ret, heredoc_cnt);
	i = -1;
	while (heredoc_str[++i])
		ret[cnt++] = ft_strdup(heredoc_str[i]);
	free(heredoc_str);
	return (ret);
}