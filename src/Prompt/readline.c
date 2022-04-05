/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyujlee <kyujlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:58:45 by kyujlee           #+#    #+#             */
/*   Updated: 2022/04/05 22:00:28 by kyujlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	read_line(t_list *env_list, char **line)
{
	char	*info;

	info = ft_colorstr(get_node(env_list, get_position(env_list, "PWD"))->data);
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
