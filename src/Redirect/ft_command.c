/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 01:59:28 by gshim             #+#    #+#             */
/*   Updated: 2022/03/28 02:52:45 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_command(t_tree_node *root, t_list *env)
{
	int pid;

	//check_builtIn : 빌트인명령이라면 부모프로세스에서 수행됩니다.
	if (execute_builtin(root->command, env) == 0)
		return (0);

	//자식프로세스 생성
	if ((pid = fork()) == -1) printf("FORK ERROR\n");
	else if (pid == 0)
	{
		// child's process
		execute(root->command, env);
		printf("AFTER execute\n");
		exit(1);
	}
	else
	{
		// parent's process
		pid = wait(NULL);
	}
	return (0);
}
