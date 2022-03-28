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

	// 1. chdir의 대상으로 argv를 입력.
	getcwd(dir, sizeof(dir));
	chdir(argv[1]);
	if (getcwd(dir, sizeof(dir)) == NULL)
	{
		strerror(errno);
	}

	// 2. 현재 경로를 환경변수에 최신화.
	node = search_node(env, "PWD");
	free(node->data);
	node->data = ft_strdup(getcwd(dir, sizeof(dir)));
}

void ft_pwd()
{
	char dir[512];

	getcwd(dir, 512);
	printf("%s\n", dir);
}

// 환경변수를 출력한다. 이때 env는 최신화가 되어있어야 겠네...
void ft_export(t_list *env)
{
	char **envv;
	int i;

	// env의 var기준으로 오름차순정렬하는 로직이 필요함.
	envv = gather(env);
	i = 0;
	printf("[EXPORT]\n");
	while(envv[i])
	{
		if (ft_strncmp(envv[i], "_=", 2))	// 이건 출력하면 안됨.
			printf("declare -x %s\n", envv[i]);
		i++;
	}
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
//		env에는 환경변수 _가 추가로 존재.
//		export는 var를 기준으로 오름차순으로 정렬해야 함.
// 32줄 vs 33줄....???
void ft_env(t_list *env)
{
	char **envv;
	int i;

	envv = gather(env);
	i = 0;
	printf("[ENV]\n");
	// 환경변수 싹다출력
	while(envv[i])
	{
		printf("%s\n", envv[i]);
		i++;
	}
}

// void exit(char **env)
// {

// }
