/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 01:53:31 by gshim             #+#    #+#             */
/*   Updated: 2022/04/06 18:34:42 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pipe(t_tree_node *root, t_list *env)
{
	int	pid;
	int	pipe_fd[2];
	int	status;

	pid = pipe(pipe_fd);
	if (pid == -1)
		printf("ERROR\n");
	pid = fork();
	if (pid == -1)
		printf("ERROR\n");
	// child's process, pipeline Input
	if (pid == 0)
	{
		dup2(pipe_fd[1], 1);	// 표준출력을 파이프라인입력으로 덮어쓰기
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		_pre_traverse(root->left, env, 0);
		exit(errno);
	}
	// parent's process, pipeline OUTPUT
	else
	{
		wait(&status);
		set_status(env, status);
		dup2(pipe_fd[0], 0);	// 표쥰입력을 파이프라인출력으로 덮어쓰기
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		_pre_traverse(root->right, env, 0);
	}
	return (0);
}
