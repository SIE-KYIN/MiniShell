/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyujlee <kyujlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 22:45:00 by kyujlee           #+#    #+#             */
/*   Updated: 2022/04/05 22:45:02 by kyujlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	str_in_quote(char *line, int i, int single_flag, int double_flag)
{
	int	tmp1;
	int	tmp2;

	tmp1 = 2;
	tmp2 = 2;
	while (tmp1 != single_flag && tmp2 != double_flag && line[++i])
	{
		if (single_flag == tmp1 - 2 && line[i] == '"')
		{
			if (line[i - 1] == '\\')
				continue ;
			(double_flag)++;
		}
		else if (double_flag == tmp2 - 2 && line[i] == '\'')
		{
			if (line[i - 1] == '\\')
				continue ;
			(single_flag)++;
		}
	}
	return (i);
}

int	is_valid_s_c(char c)
{
	(void)c;
	if (c == ';')
		return (0);
	return (1);
}
