/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:58:45 by kyujlee           #+#    #+#             */
/*   Updated: 2022/04/07 17:25:18 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	read_line(t_list *env_list, char **line)
{
	char	*info;
	char *pwd;

	if (!ft_strcmp(env_list->top.data, "0"))
		pwd = ft_strjoin(" ✅ ", search_node(env_list, "PWD")->data);
	else
		pwd = ft_strjoin(" ❌ ", search_node(env_list, "PWD")->data);
	info = ft_colorstr(pwd);
	*line = readline(info);

	free(info);
	if (*line == NULL)
	{
		delete_list(env_list);
		exit(0);
	}
	if (*line[0] == '\0')
		return (0);
	add_history(*line);
	return (1);
}
