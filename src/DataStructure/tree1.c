/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 01:14:59 by gshim             #+#    #+#             */
/*   Updated: 2022/04/08 09:14:53 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree_node	*create_node(t_tree_node *left, t_tree_node *right, char **command)
{
	t_tree_node	*new;

	new = malloc(sizeof(t_tree_node));
	if (!new)
		return (NULL);
	if (command)
		new->command = command;
	else
		new->command = NULL;
	new->left = left;
	new->right = right;
	return (new);
}

t_tree_node	*insert_root(t_tree *tree, char **command, int flag)
{
	t_tree_node	*new;

	new = create_node(NULL, NULL, command);
	new->flag = flag;
	tree->root_node = new;
	return (new);
}

t_tree_node	*insert_left(t_tree_node *parent, char **command, int flag)
{
	t_tree_node	*new;

	new = create_node(NULL, NULL, command);
	new->flag = flag;
	parent->left = new;
	return (new);
}

t_tree_node	*insert_right(t_tree_node *parent, char **command, int flag)
{
	t_tree_node	*new;

	new = create_node(NULL, NULL, command);
	new->flag = flag;
	parent->right = new;
	return (new);
}
