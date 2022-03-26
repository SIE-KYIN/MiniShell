/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:46:41 by gshim             #+#    #+#             */
/*   Updated: 2022/03/25 19:54:09 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define STDOUT_SIMPLE O_RDWR|O_CREAT|O_TRUNC
#define STDOUT_DOUBLE O_RDWR|O_CREAT|O_APPEND
#define STDIN_SIMPLE O_RDONLY
#define STDIN_DOUBLE O_RDONLY

// dup(a, b) -> a
// flag까지 갈것 없이 바로 open을 수행하여 코드양을 줄여보자.
int redir_out(t_tree_node *root, t_tree_node *right)
{
	int fd;

	// 리다이렉션 존재여부 판단
	if(!strcmp(root->command, ">"))
		fd = open(right->argument, STDOUT_SIMPLE, 0644);
	else if(!strcmp(root->command, ">>"))
		fd = open(right->argument, STDOUT_DOUBLE, 0644);
	else
		return 0;

	if (fd == -1)
	{
		perror(right->argument);
		return -1;
	}
	dup2(fd, 1);    // 표준출력의 방향은 1 -> fd
	close(fd);
	return 0;
}

int redir_in(t_tree_node *root, t_tree_node *right)
{
	int fd;

	// 리다이렉션 존재여부 판단
	if(!strcmp(root->command, "<"))
		fd = open(right->argument, STDIN_SIMPLE, 0644);
	// else if(!strcmp(root->command, "<<"))
	// 	fd = open(right->argument, STDOUT_DOUBLE, 0644);	// 기능 모르겠음.
	else
		return 0;

	if (fd == -1)
	{
		perror(right->argument);
		return -1;
	}
	dup2(fd, 0);    // 표준출력의 방향은 1 -> fd
	close(fd);
	return 0;
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
