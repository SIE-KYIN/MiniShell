/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:23:29 by gshim             #+#    #+#             */
/*   Updated: 2022/03/30 18:36:44 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envv)
{
    char *line;
    t_list *env_list;
    t_tree *token_tree;

	env_list = NULL;
	(void)argv;
    if (argc != 1)
        return (-1);

	// 이 형태로 하면 ./minishell이 계속해서 쉘 프로그램 프로세스를 키게된다.
    // while(1)
    // {
    //     int pid = fork();
    //     // child process
    //     if(pid == 0)
    //     {
    //         print_intro();
    //         env_list = parse_envv(envv);
    //         gather(env_list);
    //         sigHandler();
    //         while (1)
    //         {
    //             read_line(env_list, &line);
    //             check_syntax(line);
    //             //line에 들어있는 문자열 파싱하는 함수
    //             token_tree = tokenize(line, env_list);

    //             pre_traverse(token_tree, env_list);
    //             //-----------------------------------내 역할 끝??
    //             //파싱한 자료구조(이진트리 예상)에서 빌트인 처리, 리디렉션 처리
    //             //리스트로 할 수 있는데 이진트리가 탐색하기 쉬움 (정확히는 재귀하향트리)

    //             //free(line); [gshim] : pointer being freed was not allocated오류가 발생한다.
    //         }
    //     }
    //     else if(pid > 0)
    //         wait(0);
    //     else
    //         return (-1);
    // }

	// 디버그를 위해 부모프로세스에서 쉘을 동작시키는 코드
	print_intro();
	env_list = parse_envv(envv);
	gather(env_list);
	sigHandler();
	while (1)
	{
		read_line(env_list, &line);

		// 빈 입력을 받았을때
		// if(*line == '\0')
		// 	continue;
		// 공백입력을 받았을때....?!


		check_syntax(line);
		//line에 들어있는 문자열 파싱하는 함수
		token_tree = tokenize(line, env_list);

		pre_traverse(token_tree, env_list);
		//-----------------------------------내 역할 끝??
		//파싱한 자료구조(이진트리 예상)에서 빌트인 처리, 리디렉션 처리
		//리스트로 할 수 있는데 이진트리가 탐색하기 쉬움 (정확히는 재귀하향트리)

		//free(line); [gshim] : pointer being freed was not allocated오류가 발생한다.
	}


    delete_list(env_list);
    ft_error(1);
    return (0);
}


// 컴파일 방법 : gcc Parsing/* DataStructure/* Prompt/* Utilities/* minishell.c -lreadline -L/Users/kyujlee/.brew/opt/readline/lib -I/Users/kyujlee/.brew/opt/readline/include


/*
ctrl c 연속시 정상작똥
다른 입력 후 ctrl c 시 첫번째 동작x
aa -> ctrl c

printf -> redisplay => printf가 프롬프트를 덮어쓰고있음
redisplay -> printf => 프롬프트 뒤에 printf가 나옴
*/
