/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 01:44:11 by gshim             #+#    #+#             */
/*   Updated: 2022/04/08 01:44:45 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list_node	*search_node(t_list *list, char *var)
{
	t_list_node	*node;

	node = list->top.next;
	while (node)
	{
		if (!ft_strcmp(node->var, var))
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	free_node(t_list_node *node)
{
	if (node->data)
		free(node->data);
	if (node->var)
		free(node->var);
	free(node);
}

void	delete_node(t_list *list, char *var)
{
	t_list_node	*node;

	node = search_node(list, var);
	if (!node->next)
		node->prev->next = NULL;
	else
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	free_node(node);
	list->cnt -= 1;
}
