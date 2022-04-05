/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyujlee <kyujlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:50:09 by kyujlee           #+#    #+#             */
/*   Updated: 2022/04/05 21:53:46 by kyujlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_node(t_list *list, int position, char *var, char *data)
{
	t_list_node	*pre_node;
	t_list_node	*new_node;
	t_list_node	*next_node;

	pre_node = NULL;
	new_node = NULL;
	next_node = NULL;
	if (0 <= position && position <= list->cnt)
	{
		new_node = (t_list_node *)malloc(sizeof(t_list_node));
		new_node->var = var;
		new_node->data = data;
		new_node->next = NULL;
		pre_node = get_node(list, position);
		if (pre_node->next)
			next_node = pre_node->next;
		pre_node->next = new_node;
		new_node->prev = pre_node;
		if (next_node)
		{
			new_node->next = next_node;
			next_node->prev = new_node;
		}
		list->cnt++;
	}
}

t_list_node	*get_node(t_list *list, int position)
{
	int			i;
	t_list_node	*node;

	i = -1;
	if (list)
	{
		node = &(list->top);
		while (++i < position)
			node = node->next;
		return (node);
	}
	else
		return (NULL);
}

void	remove_node(t_list *list, int position)
{
	t_list_node	*pre_node;
	t_list_node	*curr_node;

	if (list)
	{
		if (0 <= position && position <= list->cnt)
		{
			pre_node = get_node(list, position);
			curr_node = pre_node->next;
			pre_node->next = curr_node->next;
			if (curr_node->next)
				curr_node->next->prev = pre_node;
			free(curr_node);
			list->cnt--;
		}
	}
}

int	get_position(t_list *list, char *str)
{
	int			i;
	t_list_node	*node;

	i = 0;
	node = &(list->top);
	while (i < list->cnt)
	{
		if (is_same(node->var, str))
			break ;
		i++;
		node = node->next;
	}
	if (i < list->cnt)
		return (i);
	else
		return (-1);
}
