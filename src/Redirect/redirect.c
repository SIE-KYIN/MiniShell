/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:46:41 by gshim             #+#    #+#             */
/*   Updated: 2022/04/06 23:00:57 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 리다이렉션이나 파이프라면 0, 명령어 노드라면 1을 반환한다.
// static int is_command(t_tree_node *root)
// {
// 	if (!ft_strcmp(root->command[0], "<") || !ft_strcmp(root->command[0], "<<"))
// 		return (0);
// 	else if (!ft_strcmp(root->command[0], ">") || !ft_strcmp(root->command[0], ">>"))
// 		return (0);
// 	else if (!ft_strcmp(root->command[0], "|"))
// 		return (0);
// 	else
// 		return (1);
// }

// 리다이렉션의 자손이 heredoc이면 표준입출력을 바꾸지 않는다.
// static bool nesting_condition(t_tree_node *root)
// {
// 	if (is_command(root->left))
// 	{
// 		if (!ft_strcmp(root->command[0], "<<"))
// 			return (true);
// 		else if (!ft_strcmp(root->command[0], "<"))
// 			return (true);
// 		else
// 			return (true);
// 	}
// 	else
// 	{
// 		if (!ft_strcmp(root->command[0], "<<"))
// 			return (false);
// 		else
// 			return (true);
// 	}
// }

int redir_out(t_tree_node *root, t_tree_node *right, bool flag)
{
	int fd;
	(void)flag;
	// 리다이렉션 존재여부 판단
	if(!ft_strcmp(root->command[0], ">"))
		fd = open(right->command[0], STDOUT_SIMPLE, 0644);
	else if(!ft_strcmp(root->command[0], ">>"))
		fd = open(right->command[0], STDOUT_DOUBLE, 0644);
	else
		return 0;

	if (fd == -1)
	{
		strerror(errno);
		return (-1);
	}
	// if(flag)
	// 	dup2(fd, 1);    // 표준출력의 방향은 1 -> fd
	dup2(fd, 1);
	close(fd);
	return 0;
}

// <, <<를 별도의 함수로 분리하는 것이 좋을 듯.
int redir_in(t_tree_node *root, t_tree_node *right, bool flag)
{
	int fd;
	(void)flag;
	if(!ft_strcmp(root->command[0], "<"))
	{
		fd = open(right->command[0], STDIN_SIMPLE, 0644);
		if (fd == -1)
		{
			perror(right->command[0]);
			return -1;
		}
		// if (flag)
		// 	dup2(fd, 0);
		dup2(fd, 0);
		close(fd);
		return (0);
	}
	else if(!ft_strcmp(root->command[0], "<<"))
	{
		int heredocflag = open(".heredoc", O_RDWR, 0644);
		close(heredocflag);
		heredoc(right, 0, heredocflag);
		fd = open(".heredoc", O_RDONLY, 0644); // 왜 다시열어야 동작?
		// if (flag)
		// 	dup2(fd, 0);
		dup2(fd, 0);
		return (0);
	}
	else
		return (0);
}



// int pipe_gshim(char **cmd)
// {
// 	int i;
// 	int k = 0;
// 	pid_t pid1, pid2;
// 	int fd[2];
// 	int status1,status2;

// 	// cmd에서 파이프를 기준으로 앞과 뒤를 구분한다.

// 	pipe(fd);

// 	pid1 = fork();
// 	switch(pid1)// 앞명령어 프로세스생성
// 	{
// 		case -1: perror("fork error"); break;
// 		case 0:

// 	}
// }
