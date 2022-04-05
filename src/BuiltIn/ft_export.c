/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:13:59 by gshim             #+#    #+#             */
/*   Updated: 2022/04/04 16:42:20 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 정렬을 해야하나...?
static void ft_export_no_arg(t_list *env)
{
	t_list_node *node;

	node = env->top.next;
	while(node)
	{
		if (ft_strncmp(node->var, "_", 1))	// 이거 널문자까지 비교해야되서 2로 바꾸고 내장함수도 수정해야할듯..
		{
			printf("declare -x %s", node->var);
			if (node->data)
				printf("=\"%s\"\n", node->data);
			else
				printf("\n");
		}
		node = node->next;
	}
}

static void ft_export_arg(char *argv[], t_list *env)
{
	t_list_node *node;
	int equal;
	char *var;
	char *data;

	equal = (int)(ft_strchr(argv[1], '=') - argv[1]);
	if (equal <= 0)	// '='가 없으면 추가 로직만 존재.
	{
		if(!search_node(env, argv[1])) // 이미 존재하는 환경변수라면 무시하고, 없으면 추가한다.
			add_node(env, env->cnt, ft_strdup(argv[1]), NULL);
		return ;
	}
	var = ft_substr(argv[1], 0, equal);
	data = ft_substr(argv[1], equal + 1, ft_strlen(argv[1]) - equal - 1);
	node = search_node(env, var);
	// 이미 존재한다면 덮어쓰기
	if (node)
	{
		free(node->data);
		node->data = data;
		free(var);
	}
	// 새로 생성
	else
		add_node(env, env->cnt, var, data);
}

void ft_export(char *argv[], t_list *env)
{
	if (argv[1] == NULL)
		ft_export_no_arg(env);
	else
		ft_export_arg(argv, env);
}
