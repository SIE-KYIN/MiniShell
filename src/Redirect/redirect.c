/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:46:41 by gshim             #+#    #+#             */
/*   Updated: 2022/04/04 21:32:20 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define STDOUT_SIMPLE O_RDWR|O_CREAT|O_TRUNC
#define STDOUT_DOUBLE O_RDWR|O_CREAT|O_APPEND
#define STDIN_SIMPLE O_RDONLY
#define HEREDOC O_RDWR|O_CREAT

// dup(a, b) -> a
// flag가 true면 연속된 리다이렉션 동작을 의미함 => 파일을 열되, 리디렉션 ㄴㄴ
int redir_out(t_tree_node *root, t_tree_node *right, bool flag)
{
	int fd;

	// 리다이렉션 존재여부 판단
	if(!ft_strcmp(root->command[0], ">"))
		fd = open(right->command[0], STDOUT_SIMPLE, 0644);
	else if(!ft_strcmp(root->command[0], ">>"))
		fd = open(right->command[0], STDOUT_DOUBLE, 0644);
	else
		return 0;

	if (fd == -1)
	{
		perror(right->command[0]);
		return -1;
	}
	if(flag)
		dup2(fd, 1);    // 표준출력의 방향은 1 -> fd
	close(fd);
	return 0;
}

// <, <<를 별도의 함수로 분리하는 것이 좋을 듯.
int redir_in(t_tree_node *root, t_tree_node *right, bool flag)
{
	int fd;

	fd = 0;
	// 리다이렉션 존재여부 판단
	if(!ft_strcmp(root->command[0], "<"))
		fd = open(right->command[0], STDIN_SIMPLE, 0644);
	else if(!ft_strcmp(root->command[0], "<<"))
	{
		//heredoc의 중첩처리
		// if (!flag) // heredoc이 연속되었다면
		// {
		// 	unlink(".heredoc");
		// }

		fd = open(".heredoc", STDOUT_SIMPLE, 0644);
		if (fd == -1){
			printf("open fail\n");
		}
		heredoc(root, right, fd);

		// 왜 다른모드로 다시 열어야 동작하는거지?
		close(fd);
		fd = open(".heredoc", O_RDONLY, 0644);
	}
	else
		return 0;

	if (fd == -1)
	{
		perror(right->command[0]);
		return -1;
	}
	if(flag)
		dup2(fd, 0);    // 표준출력의 방향은 1 -> fd
	close(fd);
	return 0;
}

// 리다이렉션이나 파이프라면 0, 명령어 노드라면 1을 반환한다.
int is_command(t_tree_node *root)
{
	if (!ft_strcmp(root->command[0], "<") || !ft_strcmp(root->command[0], "<<"))
		return (0);
	else if (!ft_strcmp(root->command[0], ">") || !ft_strcmp(root->command[0], ">>"))
		return (0);
	else if (!ft_strcmp(root->command[0], "|"))
		return (0);
	else
		return (1);
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
