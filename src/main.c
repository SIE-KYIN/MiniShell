#include "minishell.h"

typedef struct minishell{
	char dir[1024];
}minishell;

int redir_out(char **cmdvector){
	int i;
	int fd;

	// 리다이렉션 존재여부 판단
	for(i=0;cmdvector[i]!=NULL;i++){
		if(!strcmp(cmdvector[i], ">")) break;
	}

	if(cmdvector[i]){
		if(!cmdvector[i+1]) return -1;
		else{
			if((fd = open(cmdvector[i+1], O_RDWR|O_CREAT, 0644)) == -1){
				perror(cmdvector[i+1]);
				return -1;
			}
		}
		dup2(fd, 1);
		close(fd);
		for(;cmdvector[i+2]!=NULL;i++){
			cmdvector[i] = cmdvector[i+2];
		}
		cmdvector[i] = NULL;
	}
	return 0;
}

int main(int argc, char **argv, char **envv){
	char *cmd;

	(void)envv;
	(void)argc;
	(void)argv;
	cmd = ft_strdup("ls -al > a.txt");
	redir_out(ft_split(cmd, ' '));
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
