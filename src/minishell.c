/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:23:29 by gshim             #+#    #+#             */
/*   Updated: 2022/04/08 14:54:30 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envv)
{
	char	*line;
	t_list	*env_list;
	t_tree	*token_tree;
	t_info	info;

	info.stdin_flag = dup(0);
	(void)argv;
	env_list = NULL;
	if (argc != 1)
		return (-1);
	print_intro();
	env_list = parse_envv(envv, 0);
	while (1)
	{
		sighandler();
		read_line(env_list, &line);
		if (!check_syntax(line))
			continue ;
		token_tree = tokenize(line, env_list, &info);
		pre_traverse(token_tree, env_list, &info);
		delete_tree(token_tree);
	}
	delete_list(env_list);
	ft_error(1);
	return (0);
}
