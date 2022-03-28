#include "../minishell.h"

t_tree*		create_tree()
{
	t_tree *ret = malloc(sizeof(t_tree));
	ret->root_node = NULL;
	return (ret);
}

static void		_delete_tree(t_tree_node *root)
{
	int i;

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

void			delete_tree(t_tree* tree)
{
	if (!tree)
		return ;
	_delete_tree(tree->root_node);
	free(tree);
}
