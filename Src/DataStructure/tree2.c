#include "../../Inc/minishell.h"


t_tree*		create_tree()
{
	t_tree *ret = malloc(sizeof(t_tree));
	ret->root_node = NULL;
	return (ret);
}

static void		_delete_tree(t_tree_node *root)
{

	if (!root)
		return ;
	_delete_tree(root->left_child);
	_delete_tree(root->right_child);
	free(root->command);
	free(root->argument);
	free(root);
	
}

void			delete_tree(t_tree* tree)
{
	if (!tree)
		return ;
	_delete_tree(tree->root_node);
	free(tree);
}
