/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 01:53:31 by gshim             #+#    #+#             */
/*   Updated: 2022/03/29 21:37:06 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pipe(t_tree_node *root, t_list *env)
{
	int pid;
	int pipe_fd[2];

	pid = pipe(pipe_fd);
	if (pid == -1) printf("ERROR\n");
	pid = fork();
	if (pid == -1) printf("ERROR\n");
	// child's process, pipeline Input
	if (pid == 0)
	{
		dup2(pipe_fd[1], 1);	// 파이프의 출력을 표준출력으로 처리
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		_pre_traverse(root->left, env, 0);
		exit(0);
	}
	// parent's process, pipeline OUTPUT
	else
	{
		dup2(pipe_fd[0], 0);	// 파이프의 입력을 표준입력으로 처리
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		_pre_traverse(root->right, env, 0);
	}
	return (0);
}
