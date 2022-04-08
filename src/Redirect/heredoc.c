/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:12:47 by gshim             #+#    #+#             */
/*   Updated: 2022/04/08 09:32:20 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	heredoc_sig_int(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("%c[K\n", 27);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	heredoc_sighandler(void)
{
	signal(SIGINT, heredoc_sig_int);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc(t_tree_node *right, int flag)
{
	char	*line;
	int		fd;
	int		backup;

	backup = dup(0);
	fd = open(".heredoc", O_RDWR| O_CREAT| O_TRUNC, 0644);
	if (fd == -1)
	{
		strerror(errno);
		//return (-1);
		return ;
	}

	heredoc_sighandler();
	while(1)
	{
		line = readline("heredoc> ");
		if (line == NULL || !ft_strcmp(line, right->command[0]))
			break;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	sighandler();
	free(line);
	close(fd);
	fd = open(".heredoc", O_RDONLY, 0644);
}

