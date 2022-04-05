/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtIn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:14:38 by gshim             #+#    #+#             */
/*   Updated: 2022/04/05 16:45:24 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int execute_builtin(char **arg, t_list *env)
{
	int ret;

	if (ft_strcmp("echo", arg[0]) == 0)
		ret = ft_echo(arg);
	else if (ft_strcmp("cd", arg[0]) == 0)
		ret = ft_cd(arg, env);
	else if (ft_strcmp("pwd", arg[0]) == 0)
		ret = ft_pwd(env);
	else if (ft_strcmp("export", arg[0]) == 0)
		ret = ft_export(arg, env);
	else if (ft_strcmp("unset", arg[0]) == 0)
		ret = ft_unset(arg, env);
	else if (ft_strcmp("env", arg[0]) == 0)
		ret = ft_env(env);
    else if (ft_strcmp("exit", arg[0]) == 0)
		ret = ft_exit(arg, env);
	else
		return (-1);
	free(env->top.data);
	env->top.data = ft_itoa(ret);
	return (0);
}

// "cat", void, env
// 모든 PATH를 조회하도록
int execute(char **arg, t_list *env)
{
	char *filepath;
	char **path;
	int ret;
	int	i;

	// 현재폴더에서 실행이거나, 절대경로일때
	ret = execve(arg[0], arg, gather(env));

	// 모든 path에 대해 찾아야함.
	if(search_node(env, "PATH"))
	{
		path = ft_split(search_node(env, "PATH")->data, ':');
		i = -1;
		while(path[++i])
		{
			filepath = ft_strjoin_3(path[i], "/", arg[0]);
			ret = execve(filepath, arg, gather(env));
			free(filepath);
		}
	}
	// path를 free시켜줘야 한다.

	// 여기가 실행된다는 것은 명령어를 찾지 못했다는 뜻이다.
	if (ret != 0)
	{
		strerror(errno); // 왜 출력이 안되는걸까
		printf("minishell: %s: command not found\n", arg[0]);
	}
	return (1);
}

// 나중에 LinkedList로 옮길것.
t_list_node *search_node(t_list* list, char *var)
{
	t_list_node *node;

	node = list->top.next;

	while(node)
	{
		if (!ft_strcmp(node->var, var))
			return node;
		node = node->next;
	}
	return (NULL);
}

void free_node(t_list_node *node)
{
	if (node->data)
		free(node->data);
	if (node->var)
		free(node->var);
	free(node);
}

void delete_node(t_list* list, char *var)
{
	t_list_node *node;

	node = search_node(list, var);
	// 삭제할 노드가 맨뒤.
	if (!node->next)
	{
		node->prev->next = NULL;
		free_node(node);
	}
	// etc
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	list->cnt -= 1;
}

int	ft_pwd()
{
	char dir[512];

	getcwd(dir, 512);
	printf("%s\n", dir);
	return (0);
}

// >unset PWD
// 쉘 환경에서 변수를 제거하는 리눅스 명령어
int	ft_unset(char *argv[], t_list *env)
{
	int i;

	if (argv[1] == NULL)
		return (0);
	i = 0;
	while(argv[++i])
		delete_node(env, argv[i]);
	return (0);
}

int	ft_env(t_list *env)
{
	t_list_node *node;

	node = env->top.next;
	while(node)
	{
		// env는 data가 없으면 표시하지 않는다.
		if (node->data != NULL)
			printf("%s=%s\n", node->var, node->data);
		node = node->next;
	}
	return (0);
}

// int ft_exit_error(char *str, t_list_node *status)
// {
// 	printf("%s\n", str);
// 	free(status->data);
// 	status->data = ft_strdup("1");
// }

int	ft_exit(char *argv[], t_list *env)
{
	long long n;
	t_list_node *status;

	printf("exit\n");
	status = &(env->top);
	if (argv[1] == NULL)
		exit(0);
	else
		n = ft_atoi(argv[1]);

	// 실행인자가 2개일 경우: exit 1 1 => too many argument error => exit 안됨.
	if(ft_strcmp(argv[1], "0") && n == 0)
	{
		// 프로세스 종료상태 최신화
		free(status->data);
		status->data = ft_strdup("1");
		printf("minishell: exit: %s: numeric argument required\n", argv[1]);
		exit(1);
	}
	// 실행인자가 숫자가 아닌 경우: exit 1one2  => numberic error => exit
	else if(argv[2] != NULL)
	{
		free(status->data);
		status->data = ft_strdup("1");
		printf("minishell: exit: too many arguments\n");
	}
	else
	{ /* 정상 종료 */
		if (argv[1] < 0)
			n = 256 + n;

		// 프로세스 종료상태 최신화
		free(status->data);
		status->data = ft_strdup(argv[1]);
		exit(n);
	}
	return (0);
}
/*
bash-3.2$ exit 1one 1
exit
bash: exit: 1one: numeric argument required
종료됨.

bash-3.2$ exit 1 1one
exit
bash: exit: too many arguments
종료안됨
*/
