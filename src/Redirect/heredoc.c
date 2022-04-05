/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:12:47 by gshim             #+#    #+#             */
/*   Updated: 2022/04/05 20:56:40 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void heredoc_sig_int(int sig)
{
    if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("%c[K\n", 27);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		//ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
}

static void heredoc_sigHandler()
{
    signal(SIGINT, heredoc_sig_int);
    signal(SIGQUIT, SIG_IGN);
}

void	heredoc(t_tree_node *right, int fd)
{
	char *line;

	heredoc_sigHandler();
	while(1)
	{
		line = readline("heredoc> ");
		if (line == NULL || !ft_strcmp(line, right->command[0]))
			break;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	// 원래의 핸들러의 되돌린다.
	sigHandler();
	free(line);
}

/*
시그널처리...?
널 입력이 들어오면?

*/
