/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 01:59:28 by gshim             #+#    #+#             */
/*   Updated: 2022/04/05 16:51:34 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void command_sig_int(int sig)
{
	(void)sig;
	printf("\n");
}

static void command_sigHandler()
{
    signal(SIGINT, command_sig_int);
    signal(SIGQUIT, SIG_IGN);
}

int ft_command(t_tree_node *root, t_list *env)
{
	int pid;
	int status;
	int ret;

	command_sigHandler();
	//check_builtIn : 빌트인명령이라면 부모프로세스에서 수행됩니다.
	if (execute_builtin(root->command, env) == 0)
		return (0);

	//자식프로세스 생성
	if ((pid = fork()) == -1) printf("FORK ERROR\n");
	else if (pid == 0)
	{	// child's process
		ret = execute(root->command, env);
		strerror(errno);
		exit(errno);
	}
	else
	{	// parent's process
		pid = wait(&status);
		set_status(env, status);
	}

	sigHandler();
	return (0);
}

