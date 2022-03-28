/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:23:29 by gshim             #+#    #+#             */
/*   Updated: 2022/03/28 13:45:11 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envv)
{
    (void)argv;
    char *line;
    t_list *env_list;
    t_tree *token_tree;

	env_list = NULL;
    if (argc == 1)
    {
        print_intro();
        env_list = parse_envv(envv);
		gather(env_list);

        // search_node debug
        // t_list_node *node = search_node(env_list, "PWD");
	    // printf("var:%s, data:%s\n", node->var, node->data);

        sigHandler();
        while (1)
        {
            read_line(env_list, &line);
            check_syntax(line);
            //line에 들어있는 문자열 파싱하는 함수
            token_tree = tokenize(line, env_list);

            pre_traverse(token_tree, env_list);
            //-----------------------------------내 역할 끝??
            //파싱한 자료구조(이진트리 예상)에서 빌트인 처리, 리디렉션 처리
            //리스트로 할 수 있는데 이진트리가 탐색하기 쉬움 (정확히는 재귀하향트리)

            //free(line); [gshim] : pointer being freed was not allocated오류가 발생한다.
        }
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
