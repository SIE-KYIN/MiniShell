/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyujlee <kyujlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 22:36:48 by kyujlee           #+#    #+#             */
/*   Updated: 2022/04/05 22:37:11 by kyujlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*parse_envv(char **envv, int tmp)
{
	t_list	*list;
	char	*var;
	char	*data;
	int		i;
	int		j;

	i = -1;
	list = create_list();
	list->top.data = ft_strdup("0");
	list->top.var = ft_strdup("?");
	while (envv[++i])
	{
		j = -1;
		while (envv[i][++j])
			if (envv[i][j + 1] == '=')
				tmp = j;
		var = ft_strndup(envv[i], 0, tmp);
		data = ft_strndup(envv[i], tmp + 2, j - 1);
		add_node(list, i, var, data);
	}
	return (list);
}

char **gather(t_list *list)
{
	char **ret;
	int i;
	t_list_node *node;

	ret = malloc(sizeof(char *) * (list->cnt + 1));
	i = 0;
	node = list->top.next;
	// 모든 리스트노드에 접근
	while(i < list->cnt)
	{
		char *var = ft_strdup(node->var);
		char *data = ft_strdup(node->data);
		ret[i] = ft_strjoin_3(var, "=", data);
		free(var);
		free(data);
		node = node->next;
		i++;
	}
	ret[i] = NULL;

	// [DEBUG] 왜 파란색으로 나오지...?
	// for(int i=0;i<list->cnt;i++)
	// {
	// 	printf("%s\n", ret[i]);
	// }

	return ret;
}
