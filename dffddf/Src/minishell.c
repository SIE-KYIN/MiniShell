#include "../Inc/minishell.h"

int main(int argc, char **argv, char **envv)
{
    (void)argv;
    char *line;
    t_list *env_list;
    int pid;
    int status;

    if (argc == 1)
    {
        print_intro();
        env_list = parse_envv(envv);
        sigHandler();
        while (1)
        {
            read_line(env_list, line, envv);
            //line에 들어있는 문자열 파싱하는 함수
            //-----------------------------------내 역할 끝??
            //파싱한 자료구조(이진트리 예상)에서 빌트인 처리, 리디렉션 처리
            //리스트로 할 수 있는데 이진트리가 탐색하기 쉬움 (정확히는 재귀하향트리)

            // pid = fork();
            // if (pid == 0)    /* child process */
            // {
            //     // exec
            //     execve(command, arg);
            // }
            // else if (pid > 0) /* parent process */
            // {
            //     // wait
            //     pid = wait(NULL);
            // }
            // else {   // pid minus.... what happend..?

            // }
        }
    }
    delete_list(env_list);
    ft_error(1);
    return (0);
}

// 컴파일 방법 : gcc Parsing/* DataStructure/* Prompt/* Utilities/* minishell.c -lreadline -L/Users/kyujlee/.brew/opt/readline/lib -I/Users/kyujlee/.brew/opt/readline/include
