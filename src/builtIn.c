#include "minishell.h"

int execute_builtin(char *command, char **arg, char **env)
{
	if (ft_strncmp("echo", command, 4) == 0)
		ft_echo(arg, env);
	else if (ft_strncmp("cd", command, 2) == 0)
		ft_cd(arg, env);
	else if (ft_strncmp("pwd", command, 3) == 0)
		ft_pwd(env);
	else if (ft_strncmp("export", command, 6) == 0)
		ft_export(env);
	else if (ft_strncmp("unset", command, 5) == 0)
		ft_unset(env);
	else if (ft_strncmp("env", command, 3) == 0)
		ft_env(env);
    else if (ft_strncmp(command, "exit", 4) == 0)
		exit(1); // exit명령 처리
	else
		return (-1);
	return (0);
}

int execute(char *command, char **arg, char **env)
{
	(void)command;
	char *filepath = ft_strjoin("/bin/", arg[0]);
	execve(filepath, arg, env);
	// 이 밑이 어떻게 실행되는걸까....!!
	// quit이 arg[0]일때, 즉 해당명령을 찾지 못했다면 수행된다.
	// 이곳은 명령어가 없다는 에러문을 출력하기 좋을 것 같다.
	printf("AFTER EXEC\n");
	// 지역변수를 사용하는게 좋을듯 하다.
	free(filepath);
	exit(1);
}

// -n
void ft_echo(char *argv[], char **env)
{
	(void)argv;
	(void)env;
	printf("ECHO\n");
}

// arg : dir
// cd에 인자가 없으면 $HOME디렉토리로 이동한다.
void ft_cd(char *argv[], char **env)
{
	int i;
	char **s;
	char dir[512];

	(void)env;

	// 디렉토리 변경 -> 부모프로세스에서 변경적용이 안될듯
	// 				 환경변수 **env는 변경가능.
	chdir(argv[0]);
	getcwd(dir, 512);	// getcwd는 어디서 가져오는건지?
	// 환경변수에 저장 어떻게?
	i = -1;
	while(!argv[++i])
	{
		s = ft_split(argv[i], '=');
		if (strncmp(s[0], "PWD", 3) == 0)
		{
			printf("환경변수 PWD 발견\n");
			free(argv[i]);
			argv[i] = ft_strjoin(s[0], ft_strdup(dir));
		}
		free(s[0]);
		free(s[1]);
		free(s);
	}

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
void ft_export(char **env)
{
	printf("[EXPORT]\n");
	displayDoublyList(parse_envv(env));
}

// >unset PWD
// 쉘 환경에서 변수를 제거하는 리눅스 명령어
void ft_unset(char **env)
{
	(void)env;
	printf("UNSET\n");
}

// 옵션없으니 export랑 똑같지 않나?
// export가 주는 변수들과 env가 주는 변수들의 차이는??
// 32줄 vs 33줄....???
void ft_env(char **env)
{
	t_list *env_list;

	env_list = parse_envv(env);
	displayDoublyList(env_list);
}

// void exit(char **env)
// {

// }
