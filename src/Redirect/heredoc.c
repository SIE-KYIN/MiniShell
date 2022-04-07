/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:12:47 by gshim             #+#    #+#             */
/*   Updated: 2022/04/06 21:45:16 by gshim            ###   ########.fr       */
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

void	heredoc(t_tree_node *right, int fd2, int flag)
{
	char	*line;
	int		fd;
	int		backup;

	(void)fd2;
	backup = dup(0);
	// 이미 heredoc으로 인한 .heredoc파일이 존재하는지 확인합니다.
	if (flag != -1)
		dup2(g_stdin, 0);

	fd = open(".heredoc", STDOUT_SIMPLE, 0644);
	if (fd == -1)
	{
		strerror(errno);
		//return (-1);
		return ;
	}

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

	close(fd);
	fd = open(".heredoc", O_RDONLY, 0644); // 왜 다시열어야 동작?

	if (flag < 0)
		dup2(backup, 0);
}

/*
시그널처리...?
널 입력이 들어오면?

*/
