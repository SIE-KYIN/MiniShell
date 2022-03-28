#include "minishell.h"

int execute_builtin(char **arg, t_list *env)
{
	if (ft_strncmp("echo", arg[0], 4) == 0)
		ft_echo(arg, env);
	else if (ft_strncmp("cd", arg[0], 2) == 0)
		ft_cd(arg, env);
	else if (ft_strncmp("pwd", arg[0], 3) == 0)
		ft_pwd(env);
	else if (ft_strncmp("export", arg[0], 6) == 0)
		ft_export(env);
	else if (ft_strncmp("unset", arg[0], 5) == 0)
		ft_unset(env);
	else if (ft_strncmp("env", arg[0], 3) == 0)
		ft_env(env);
    else if (ft_strncmp(arg[0], "exit", 4) == 0)
		exit(1); // exit명령 처리
	else
		return (-1);
	return (0);
}

// "cat", void, env
// 모든 PATH를 조회하도록
int execute(char **arg, t_list *env)
{
	char *filepath;
	int ret;

	(void)env;
	filepath = ft_strjoin("/bin/", arg[0]);
	ret = execve(filepath, arg, gather(env));
	if (ret != 0)
	{
		char *error_message = strerror(errno);
		printf("%s\n", error_message);
	}
	// 이 밑이 어떻게 실행되는걸까....!!
	// quit이 arg[0]일때, 즉 해당명령을 찾지 못했다면 수행된다.
	// 이곳은 명령어가 없다는 에러문을 출력하기 좋을 것 같다.
	// 지역변수를 사용하는게 좋을듯 하다.
	free(filepath);
	return (1);
}

// 나중에 LinkedList로 옮길것.
t_list_node *search_node(t_list* list, char *var)
{
	t_list_node *node;

	node = list->top.next;

	while(node)
	{
		if (!strcmp(node->var, var))	// 나중에 libft함수로 바꿀것.
			return node;
		node = node->next;
	}
	return (NULL);
}

// -n
void ft_echo(char *argv[], t_list *env)
{
	(void)argv;
	(void)env;
	printf("ECHO\n");
}

// arg : dir
// cd에 인자가 없으면 $HOME디렉토리로 이동한다.
void ft_cd(char *argv[], t_list *env)
{
	char dir[512];
	t_list_node *node;

	(void)argv;
	(void)env;

	// 1. chdir의 대상으로 argv를 입력.
	getcwd(dir, sizeof(dir));
	printf("argv[0] : %s\n", argv[1]);
	printf("before cd : %s\n", dir);
	chdir(argv[0]);
	if (getcwd(dir, sizeof(dir)) == NULL)
	{
		strerror(errno);
	}
	printf("after cd : %s\n", dir);

	// 2. 현재 경로를 환경변수에 최신화.
	node = search_node(env, "PWD");
	free(node->data);
	node->data = ft_strdup(getcwd(dir, sizeof(dir)));
	displayDoublyList(env);
}

// 현재 디렉토리 출력
// getcwd를 수행하고 이를 환경변수에도 적용해야 하는가?
void ft_pwd()
{
	char dir[512];

	printf("[PWD]\n");
	getcwd(dir, 512);
	printf("%s\n", dir);

	// $PWD 수정
}

// 환경변수를 출력한다. 이때 env는 최신화가 되어있어야 겠네...
void ft_export(t_list *env)
{
	(void)env;
	printf("[EXPORT]\n");
	// [DEBUG] 왜 파란색으로 나오지...?
	// for(int i=0;i<list->cnt;i++)
	// {
	// 	printf("%s\n", ret[i]);
	// }
}

// >unset PWD
// 쉘 환경에서 변수를 제거하는 리눅스 명령어
void ft_unset(t_list *env)
{
	(void)env;
	printf("UNSET\n");
}

// 옵션없으니 export랑 똑같지 않나?
// export가 주는 변수들과 env가 주는 변수들의 차이는??
// 32줄 vs 33줄....???
void ft_env(t_list *env)
{
	// t_list_node *node;

	// node = (*env).top;
	// // [DEBUG] 왜 파란색으로 나오지...?
	// for(int i=0;i<env->cnt;i++)
	// {
	// 	printf("%s\n", env->top);
	// 	node = node->next;
	// }
	(void)env;
}

// void exit(char **env)
// {

// }
