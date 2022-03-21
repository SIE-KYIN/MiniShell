#include "../minishell.h"

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
			cmdvector[i] = cmdvector[i+2];  // 리다이렉션기호, 파일명 토큰제거
		}
		cmdvector[i] = NULL;
	}
	return 0;
}

void parse_line(char *line, char **envv)
{
    //static const char tok[] = " \t\n";
    //char *arg[100]; // MAXARG 명시필요.
    char **arg;
    //char *str;
    //char *save;
    //int argv;
    int pid;
    //int stdin_fd = dup(0); // 표준입력
    int stdout_fd = dup(1); // 표준출력

    // argv = 0;
    // str = strtok_r(line, tok, &save);
    // while (str != NULL)
    // {
    //     arg[argv++] = str;
    //     str = strtok_r(NULL, tok, &save);
    // }
    // arg[argv] = (char *)0;
    arg = ft_split(line, ' ');
    // [0]ls

    // [DEBUG]실행인자
    for(int i=0;i<4;i++){
        printf("[%d]%s\n", i, arg[i]);
    }
    redir_out(arg);
    for(int i=0;i<4;i++){
        printf("[%d]%s\n", i, arg[i]);
    }

    if (ft_strncmp(arg[0], "exit", 4) == 0) exit(1); // exit명령 처리
    if ((pid = fork()) == -1) printf("FORK ERROR\n");
    else if (pid != 0){
        pid = wait(NULL);
    }
    else{
		execute(arg[0], arg, envv);
        printf("AFTER execute\n");
    }

    // 표준출력을 원래대로 되돌린다.
    dup2(stdout_fd, 1);
}

void read_line(t_list *env_list, char *line, char **envv)
{

    char *info = ft_colorstr(get_node(env_list, get_position(env_list, "PWD"))->data);
    line = readline(info);
    free(info);
    if (line == NULL)
        exit(0);

    //printf("%s\n", line);
    parse_line(line, envv);

    add_history(line);
    free(line);
    line = NULL;
}
