/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:12:47 by gshim             #+#    #+#             */
/*   Updated: 2022/04/08 15:05:25 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	heredoc_sig_int(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "*");
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
}

static void	heredoc_sighandler(void)
{
	signal(SIGINT, heredoc_sig_int);
	signal(SIGQUIT, SIG_IGN);
}

static void	heredoc_readline(t_tree_node *right, char *line, int fd)
{
	heredoc_sighandler();
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL || !ft_strcmp(line, right->command[0])
			|| !ft_strcmp(line, "*"))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	sighandler();
}

int	heredoc(t_tree_node *right, t_info *info)
{
	char	*line;
	int		fd;
	int		backup_fd;

	backup_fd = dup(0);
	dup2(info->stdin_flag, 0);
	fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (fd);
	line = NULL;
	heredoc_readline(right, line, fd);
	free(line);
	close(fd);
	fd = open(".heredoc", O_RDONLY, 0644);
	dup2(backup_fd, 0);
	return (fd);
}
