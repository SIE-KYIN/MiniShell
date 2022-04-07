/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:13:59 by gshim             #+#    #+#             */
/*   Updated: 2022/04/07 17:51:10 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 정렬을 해야하나...?
static void	ft_export_no_arg(t_list *env)
{
	t_list_node	*node;

	node = env->top.next;
	while (node)
	{
		if (ft_strcmp(node->var, "_"))
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

static int	ft_export_error(char *arg)
{
	if (arg[1] != '\0')
	{
		printf("bash: export: '%s': not a valid identifier\n", arg);
		return (-1);
	}
	else
		return (0);
}

static int	ft_export_arg(char *arg, t_list *env)
{
	t_list_node	*node;
	char		*equal;
	char		*var;
	char		*data;

	if (arg[0] == '?')
		ft_export_error(arg);
	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		if (!search_node(env, arg))
			add_node(env, env->cnt, ft_strdup(arg), NULL);
		return (0);
	}
	*equal = '\0';
	var = ft_strdup(arg);
	data = ft_strdup(equal + 1);
	node = search_node(env, var);
	if (node)
	{
		free(node->data);
		node->data = data;
		free(var);
	}
	else
		add_node(env, env->cnt, var, data);
	return (0);
}

int	ft_export(char *argv[], t_list *env)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (argv[1] == NULL)
		ft_export_no_arg(env);
	else
		while (argv[++i])
			ret += ft_export_arg(argv[i], env);
	return (ret < 0);
}
