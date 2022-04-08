/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyujlee <kyujlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:57:27 by kyujlee           #+#    #+#             */
/*   Updated: 2022/04/05 21:57:59 by kyujlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*create_tree(void)
{
	t_tree	*ret;

	ret = malloc(sizeof(t_tree));
	ret->root_node = NULL;
	return (ret);
}

static void	_delete_tree(t_tree_node *root)
{
	int	i;

	if (!root)
		return ;
	_delete_tree(root->left);
	_delete_tree(root->right);
	i = -1;
	while (root->command[++i])
		free(root->command[i]);
	free(root->command);
	free(root);
}

void	delete_tree(t_tree	*tree)
{
	if (!tree)
		return ;
	_delete_tree(tree->root_node);
	free(tree);
}
