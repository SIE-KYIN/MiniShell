/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 01:59:28 by gshim             #+#    #+#             */
/*   Updated: 2022/04/01 15:19:17 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_command(t_tree_node *root, t_list *env)
{
	int pid;
	int status;
	int ret;

	//check_builtIn : 빌트인명령이라면 부모프로세스에서 수행됩니다.
	if (execute_builtin(root->command, env) == 0)
		return (0);

	//자식프로세스 생성
	if ((pid = fork()) == -1) printf("FORK ERROR\n");
	else if (pid == 0)
	{
		// child's process
		ret = execute(root->command, env);
		printf("errno: %d\n", errno);
		env->top.data = ft_itoa(errno);
		exit(ret);
	}
	else
	{
		// parent's process
		pid = wait(&status);	// status는 8진수 WIFEXITED(statloc), WTERMSIG(statloc)

		// 종료상태를 출력한다.(나중에 함수화할 것)

		if (WIFEXITED(status))
		{ /* 정상 종료 */
			printf("1|%d|\n", WEXITSTATUS(status));
		}
		else
		{ /* 비정상 종료 */
			printf("2|%d|\n", WTERMSIG(status));
		}

	}
	return (0);
}
