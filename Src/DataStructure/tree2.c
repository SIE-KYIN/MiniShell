#include "../../Inc/minishell.h"


t_tree*		create_tree(t_tree_node root)
{
	t_tree *ret = malloc(sizeof(t_tree));
	t_tree_node *new = malloc(sizeof(t_tree_node));
	new->left_child = NULL;
	new->right_child = NULL;
	new->data = root.data;
	ret->root_node = new;
	return (ret);
}

static void		_delete_tree(t_tree_node *root)
{

	if (!root)
		return ;
	_delete_tree(root->left_child);
	_delete_tree(root->right_child);
	free(root);
}

void			delete_tree(t_tree* tree)
{
	if (!tree)
		return ;
	_delete_tree(tree->root_node);
	free(tree);
}
