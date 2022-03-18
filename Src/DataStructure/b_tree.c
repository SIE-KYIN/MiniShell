#include "../../Inc/minishell.h"

t_tree_node	*create_node(t_tree_node *left, t_tree_node *right, char data)
{
	t_tree_node *new = malloc(sizeof(t_tree_node));
	if (!new)
		return (NULL);

	new->data = data;
	new->left_child = left;
	new->right_child = right;
	return (new);
}

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



t_tree_node*	insert_root(t_tree_node* root, t_tree_node element)
{
	t_tree_node *new = create_node(root, NULL, element.data);
	return (new);
}

t_tree_node*	insert_left(t_tree_node* parent, t_tree_node element)
{
	t_tree_node *new = create_node(NULL, NULL, element.data);
	parent->left_child = new;
	return (new);
}

t_tree_node*	insert_right(t_tree_node* parent, t_tree_node element)
{
	t_tree_node *new = create_node(NULL, NULL, element.data);
	parent->right_child= new;
	return (new);
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




static void		_pre_traverse(t_tree_node *root)
{
	if (!root)
		return ;
	printf("%c ", root->data);
	_pre_traverse(root->left_child);
	_pre_traverse(root->right_child);
	return ;
}

void	pre_traverse(t_tree *tree)
{
	t_tree_node *root;

	if (!tree)
		return ;
	root = tree->root_node;
	_pre_traverse(root);
}


t_tree *createExampleBinTree() {
    t_tree *pReturn = NULL;
    t_tree_node *pNodeA = NULL, *pNodeB = NULL, *pNodeC = NULL;
    t_tree_node *pNodeD = NULL, *pNodeE = NULL, *pNodeF = NULL;
    t_tree_node *pNodeG = NULL, *pNodeH = NULL, *pNodeI = NULL;
    t_tree_node *pNodeJ = NULL, *pNodeK = NULL, *pNodeL = NULL;
    t_tree_node *pNodeM = NULL;
    t_tree_node node = {0,};

    node.data = 'A';
    pReturn = create_tree(node);
    if (pReturn != NULL) {
        pNodeA = pReturn->root_node;
        node.data = 'B';
        pNodeB = insert_left(pNodeA, node);
        node.data = 'C';
        pNodeC = insert_right(pNodeA, node);
        if (pNodeB != NULL) {
            node.data = 'D';
            pNodeD = insert_left(pNodeB, node);
            node.data = 'E';
            pNodeE = insert_right(pNodeB, node);
        }
        if (pNodeC != NULL) {
            node.data = 'F';
            pNodeF = insert_left(pNodeC, node);
            node.data = 'G';
            pNodeG = insert_right(pNodeC, node);
        }
        if (pNodeD != NULL) {
            node.data = 'H';
            pNodeH = insert_left(pNodeD, node);
            node.data = 'I';
            pNodeI = insert_right(pNodeD, node);
        }
        if (pNodeE != NULL) {
            node.data = 'J';
            pNodeJ = insert_left(pNodeE, node);
        }
        if (pNodeF != NULL) {
            node.data = 'K';
            pNodeK = insert_right(pNodeF, node);
        }
        if (pNodeG != NULL) {
            node.data = 'L';
            pNodeL = insert_left(pNodeG, node);
            node.data = 'M';
            pNodeM = insert_right(pNodeG, node);
        }
    }

    return pReturn;
}


int main() {
    t_tree *pBinTree = NULL;
    pBinTree = createExampleBinTree();
    if (pBinTree != NULL) {
        printf("Preorder Iterative Traversal\n");
        pre_traverse(pBinTree);

        delete_tree(pBinTree);
    }

    return 0;
}
