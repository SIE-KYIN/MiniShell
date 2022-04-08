/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 01:53:31 by gshim             #+#    #+#             */
/*   Updated: 2022/04/08 02:24:56 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	child_process(t_tree_node *root, t_list *env, int pipe_fd[2])
{
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	_pre_traverse(root->left, env, 0);
	exit(errno);
}

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
	if (pid == 0)
		child_process(root, env, pipe_fd);
	else
	{
		wait(&status);
		set_status(env, get_status(status));
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		_pre_traverse(root->right, env, 0);
	}
	return (0);
}
