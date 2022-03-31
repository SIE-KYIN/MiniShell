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
		ft_export(arg, env);
	else if (ft_strncmp("unset", arg[0], 5) == 0)
		ft_unset(arg, env);
	else if (ft_strncmp("env", arg[0], 3) == 0)
		ft_env(env);
    else if (ft_strncmp("exit", arg[0], 4) == 0)
		exit(0); // exit명령 처리
	else
		return (-1);
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
	path = ft_split(search_node(env, "PATH")->data, ':');
	i = -1;
	while(path[++i])
	{
		filepath = ft_strjoin_3(path[i], "/", arg[0]);
		ret = execve(filepath, arg, gather(env));
		free(filepath);
	}

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
		if (!strcmp(node->var, var))	// 나중에 libft함수로 바꿀것.
			return node;
		node = node->next;
	}
	return (NULL);
}

void delete_node(t_list* list, char *var)
{
	t_list_node *node;

	node = list->top.next;
	while(node)
	{
		if (strcmp(node->var, var)){	// 나중에 libft함수로 바꿀것.
			node = node->next;
			continue;
		}
		// next x
		if (!node->next)
		{
			list->cnt -= 1;
			node->prev = NULL;
			free(node);
		}
		// etc
		else
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
			list->cnt -= 1;
		}
		break;
	}
}

// -n
void ft_echo(char *argv[], t_list *env)
{
	char **arg;
	int i;
	int flag;

	arg = ft_split(argv[1], ' ');
	// flag에 옵션 여부를 저장합니다., flag에 따라 arg의 읽기순서가 첫번째부턴지 두번째부턴지 달라집니다.
	flag = 0;
	if (!ft_strncmp(arg[0], "-n", 2))
		flag = 1;
	i = flag;
	while(arg[i])
	{
		if (i != flag)
			printf(" ");
		// 환경변수
		// if (arg[i][0] == '$')
		// 	printf("%s", search_node(env, arg[i] + 1)->data);
		// else
		// 	printf("%s", arg[i]);
		(void)env;
		printf("%s", arg[i]);
		i++;
	}

	// OUTPUT
	if (flag == 0)
		printf("\n");
}

void ft_cd(char *argv[], t_list *env)
{
	char dir[512];
	t_list_node *pwd;
	t_list_node *old_pwd;
	char *nextdir;

	getcwd(dir, sizeof(dir));
	// cd
	if (!argv[1])
		nextdir = search_node(env, "HOME")->data;
	// cd -
	else if (!strcmp(argv[1], "-"))
		nextdir = search_node(env, "OLDPWD")->data;
	// cd [path]
	else
		nextdir = argv[1];
	if (chdir(nextdir) == -1){
		printf("minishell: cd: %s: No such file or directory\n", nextdir);
		strerror(errno);
	}
	if (!getcwd(dir, sizeof(dir)))
		strerror(errno);
	pwd = search_node(env, "PWD");
	old_pwd = search_node(env, "OLDPWD");

	free(old_pwd->data);
	old_pwd->data = pwd->data;
	pwd->data = ft_strdup(getcwd(dir, sizeof(dir)));
}

void ft_pwd()
{
	char dir[512];

	getcwd(dir, 512);
	printf("%s\n", dir);
}

// 환경변수를 출력한다. 이때 env는 최신화가 되어있어야 겠네...
void ft_export(char *argv[], t_list *env)
{
	char **envv;
	t_list_node *ret;
	int i;
	int equal;
	char *var;
	char *data;

	i = 0;
	envv = gather(env);
	// 인자값이 없다.
	if (argv[1] == NULL)
	{
		// sort!
		while(envv[i])
		{
			if (ft_strncmp(envv[i], "_=", 2))	// 이건 출력하면 안됨.
				printf("declare -x %s\n", envv[i]);	// declare -x A="B"꼴로 출력, declare -x A 도 있을 수 있음.
			i++;
		}
	}
	// 인자값을 환경변수로 등록 => [export a] x, [export a=] o,
	// ft_substr한 것들 free해줘야함...
	else
	{
		equal = (int)(ft_strchr(argv[1], '=') - argv[1]);
		if (equal <= 0)	// equal문자가 없으면 음수값이 저장된다.
			return ;
		// 이미 존재한다면 덮어쓰기
		var = ft_substr(argv[1], 0, equal);
		data = ft_substr(argv[1], equal + 1, ft_strlen(argv[1]) - equal - 1);
		ret = search_node(env, var);
		if (ret)
		{
			free(ret->data);
			ret->data = ft_substr(argv[1], equal + 1, ft_strlen(argv[1]) - equal - 1);
		}
		// 새로 생성
		else
		{
			// '='기호가 없다면 바로 종료시킨다.
			if (ft_strchr(argv[1], '=') == NULL)
				return ;
			add_node(env, env->cnt, ft_substr(argv[1], 0, equal), ft_substr(argv[1], equal + 1, ft_strlen(argv[1]) - equal - 1));
			// free[0], free[1]은 노드가 가져야 하므로 free하지 않음
		}
	}
}

// >unset PWD
// 쉘 환경에서 변수를 제거하는 리눅스 명령어
void ft_unset(char *argv[], t_list *env)
{
	int i;

	i = 0;
	if (argv[1] == NULL)
		return ;

	delete_node(env, argv[1]);
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
	// 환경변수 싹다출력
	while(envv[i])
	{
		printf("%s\n", envv[i]);
		i++;
	}
}
