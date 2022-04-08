/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyujlee <kyujlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 22:50:55 by kyujlee           #+#    #+#             */
/*   Updated: 2022/04/05 22:50:56 by kyujlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**plus_space(char **str, int criteria)
{
	int		cnt;
	char	**ret;
	int		i;

	cnt = strcnt_double_ptr(str);
	ret = (char **)malloc(sizeof(char *) * (cnt + 2));
	i = -1;
	while (++i < cnt)
	{
		if (i < criteria)
			ret[i] = ft_strdup(str[i]);
		else
			ret[i + 1] = ft_strdup(str[i]);
	}
	ret[cnt + 1] = NULL;
	return (ret);
}

void	divide_str(char **ret, int i)
{
	char	*command;
	char	*argument;
	int		j;
	int		flag;

	command = NULL;
	argument = NULL;
	flag = 0;
	j = -1;
	while (ret[i + 2][++j])
	{
		if (!flag && ret[i + 2][j] != ' ')
			flag = 1;
		if (flag && ret[i + 2][j] == ' ')
			break ;
	}
	argument = ft_strndup(ret[i + 2], 0, j);
	command = ft_strndup(ret[i + 2], j + 1, ft_strlen(ret[i + 2]) - 1);
	ret[i] = command;
	free(ret[i + 2]);
	ret[i + 2] = argument;
}
