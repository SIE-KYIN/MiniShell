/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:12:47 by gshim             #+#    #+#             */
/*   Updated: 2022/04/01 13:09:58 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc(t_tree_node *root, t_tree_node *right, int fd)
{
	char *line;

	(void)root;
	// 무한반복
	while(1)
	{
		// readline으로 한줄씩 계속해서 입력받는다.
		line = readline("heredoc> ");
		// 한줄이 right->command[0]와 일치하면 루프를 빠져나온다. [break]
		if (!strcmp(line, right->command[0]))
			break;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
}

/*
시그널처리...?
널 입력이 들어오면?

*/