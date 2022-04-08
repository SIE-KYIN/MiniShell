/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtIn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:14:38 by gshim             #+#    #+#             */
/*   Updated: 2022/04/08 02:06:32 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	dir[512];

	getcwd(dir, 512);
	printf("%s\n", dir);
	return (0);
}

int	ft_unset(char *argv[], t_list *env)
{
	int	i;

	if (argv[1] == NULL)
		return (0);
	i = 0;
	while (argv[++i])
		delete_node(env, argv[i]);
	return (0);
}

int	ft_env(t_list *env)
{
	t_list_node	*node;

	node = env->top.next;
	while (node)
	{
		if (node->data != NULL)
			printf("%s=%s\n", node->var, node->data);
		node = node->next;
	}
	return (0);
}
