/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 01:59:28 by gshim             #+#    #+#             */
/*   Updated: 2022/04/07 17:11:59 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// handler 를 cat때문에 적용??
int	ft_command(t_tree_node *root, t_list *env)
{
	int	pid;
	int	status;
	int	ret;

	if (execute_builtin(root->command, env) == 0)
		return (0);

	if ((pid = fork()) == -1)
		printf("FORK ERROR\n");
	else if (pid == 0)
	{	// child's process
		ret = execute(root->command, env);
		strerror(errno);
		exit(errno);
	}
	else
	{	// parent's process
		disable_signal();
		pid = wait(&status);
		set_status(env, status);
	}
	return (0);
}
