#include <stdio.h>
#include <unistd.h>	//getcwd
#include <dirent.h>
#include "libft.h"

typedef struct minishell{
	char dir[1024];
}minishell;

int main(){
	//minishell m;
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
}
// 부모프로세스 shell > pwd

// 자식프로세스 cd ..