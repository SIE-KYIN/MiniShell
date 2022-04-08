/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 01:46:43 by gshim             #+#    #+#             */
/*   Updated: 2022/04/08 02:25:51 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	non_numeric_handle(char *arg, t_list_node *status)
{
	free(status->data);
	status->data = ft_strdup("1");
	printf("minishell: exit: %s: numeric argument required\n", arg);
	exit(1);
}

static void	many_arg_handle(t_list_node *status)
{
	free(status->data);
	status->data = ft_strdup("1");
	printf("minishell: exit: too many arguments\n");
}

int	ft_exit(char *argv[], t_list *env)
{
	long long	n;
	t_list_node	*status;

	printf("exit\n");
	status = &(env->top);
	if (argv[1] == NULL)
		exit(0);
	n = ft_atoi(argv[1]);
	if (argv[1] < 0)
		n = 256 + n;
	else
		n %= 255;
	if (ft_strcmp(argv[1], "0") && n == 0)
		non_numeric_handle(argv[1], status);
	else if (argv[2] != NULL)
		many_arg_handle(status);
	else
	{
		free(status->data);
		status->data = ft_strdup(argv[1]);
		exit(n);
	}
	return (0);
}
