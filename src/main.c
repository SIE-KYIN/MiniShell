#include "minishell.h"

typedef struct minishell{
	char dir[1024];
}minishell;

int main(int argc, char **argv, char **envv){
	int fd[2];
	int pipe_val;
	pid_t pid;
	char buff[100];

	pipe_val = pipe(fd);	// 파이프입구출구 fd[1] -> fd[0]
	if(pipe_val == -1) printf("ERROR\n");
	pid = fork();
	if(pid == -1) printf("ERROR\n");

	// 부모프로세스는 파이프의 출구에서 값을 읽어온다.
	if(pid > 0)
	{
		// parent's process
		wait(0);
		read(fd[0], buff, 100);
		printf("%s\n", buff);
	}
	// 자식프로세스는 파이프의 입구로 값을 입력한다.
	else if(pid == 0)
	{
		// child's process
		char *str = "|Hello, parent|";
		write(fd[1], str, strlen(str));
	}
}
/*
	char dir[1024];

	// 현재 디렉토리 출력
	getcwd(dir, 1024);
	printf("%s\n", dir);

	// 디렉토리 이동
	chdir("../");
	getcwd(dir, 1024);
	printf("%s\n", dir);

	// 디렉토리 탐색
	struct dirent *dir_entry;
	DIR* a;
	a = opendir(".");
	if ( NULL != a)
	{
		while((dir_entry  = readdir(a)))
		{ // 디렉토리 안에 있는 모든 파일과 디렉토리 출력
			printf( "%s\n", dir_entry->d_name);
		}
		closedir(a);
	}

*/
