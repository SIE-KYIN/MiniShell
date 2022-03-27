#include "../../Inc/minishell.h"

t_tree_node	*create_node(t_tree_node *left_child, t_tree_node *right_child, char **command)
{
	t_tree_node *new = malloc(sizeof(t_tree_node));
	if (!new)
		return (NULL);
	if (command)
		new->command = command;
	else
		new->command = NULL;
	new->left = left_child;
	new->right = right_child;
	return (new);
}

t_tree_node*	insert_root(t_tree* tree, char **command, int flag)
{
	t_tree_node *new = create_node(NULL, NULL,  command);
	new->flag = flag;
	tree->root_node = new;
	return (new);
}

t_tree_node*	insert_left(t_tree_node* parent,  char **command, int flag)
{
	t_tree_node *new = create_node(NULL, NULL, command);
	new->flag = flag;
	parent->left = new;
	return (new);
}

t_tree_node*	insert_right(t_tree_node* parent, char **command, int flag)
{
	t_tree_node *new = create_node(NULL, NULL,  command);
	new->flag = flag;
	parent->right= new;
	return (new);
}

//전위순회
static void		_pre_traverse(t_tree_node *root)
{
	if (!root)
		return ;
	// printf("%s|", root->command[0]);
	// printf("%s\n", root->command[1]);
	printf ("%d\n", root->flag);
	_pre_traverse(root->left);
	_pre_traverse(root->right);
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

// static void		_in_traverse(t_tree_node *root)
// {
// 	if (!root)
// 		return ;
	
// 	_in_traverse(root->left);
// 	printf("%s   |", root->command);
// 	printf("%d \n", root->flag);
// 	_in_traverse(root->right);
// 	return ;
// }

// void	in_traverse(t_tree *tree)
// {
// 	t_tree_node *root;

// 	if (!tree)
// 		return ;
// 	root = tree->root_node;
// 	_in_traverse(root);
// }


// static void		_post_traverse(t_tree_node *root)
// {
// 	if (!root)
// 		return ;
	
// 	_in_traverse(root->left);
// 	_in_traverse(root->right);
// 	printf("%s   |", root->command);
// 	printf("%d \n", root->flag);
// 	return ;
// }

// void	post_traverse(t_tree *tree)
// {
// 	t_tree_node *root;

// 	if (!tree)
// 		return ;
// 	root = tree->root_node;
// 	_post_traverse(root);
// }

// t_tree *createExampleBinTree() {
//     t_tree *pReturn = NULL;
//     t_tree_node *pNodeA = NULL, *pNodeB = NULL, *pNodeC = NULL;
//     t_tree_node *pNodeD = NULL, *pNodeE = NULL, *pNodeF = NULL;
//     t_tree_node *pNodeG = NULL, *pNodeH = NULL, *pNodeI = NULL;
//     t_tree_node *pNodeJ = NULL, *pNodeK = NULL, *pNodeL = NULL;
//     t_tree_node *pNodeM = NULL;
//     t_tree_node node = {0,};
// 	char **tmp;

    
//     pReturn = create_tree();
//     if (pReturn != NULL) {
// 		tmp = (char **)malloc(sizeof(char *) * 3);
// 		tmp[0] = ft_strdup
//         pNodeA = insert_root(pReturn, NULL, 0);
        
//         pNodeB = insert_left(pNodeA, NULL, 1);
        
//         pNodeC = insert_right(pNodeA,NULL, 2);
//         if (pNodeB != NULL) {
            
//             pNodeD = insert_left(pNodeB, NULL, 3);
            
//             pNodeE = insert_right(pNodeB,NULL, 4);
//         }
//         if (pNodeC != NULL) {
            
//             pNodeF = insert_left(pNodeC, NULL, 5);
            
//             pNodeG = insert_right(pNodeC, NULL,6);
//         }
//         if (pNodeD != NULL) {
            
//             pNodeH = insert_left(pNodeD, NULL, 7);
            
//             pNodeI = insert_right(pNodeD, NULL, 8);
//         }
//         if (pNodeE != NULL) {
            
//             pNodeJ = insert_left(pNodeE, NULL, 9);
//         }
//         if (pNodeF != NULL) {
            
//             pNodeK = insert_right(pNodeF, NULL, 10);
//         }
//         if (pNodeG != NULL) {
            
//             pNodeL = insert_left(pNodeG, NULL, 11);
            
//             pNodeM = insert_right(pNodeG, NULL, 12);
//         }
//     }

//     return pReturn;
// }


// void  ho()
// {
// 	t_tree *pBinTree = NULL;
//     pBinTree = createExampleBinTree();
//     if (pBinTree != NULL) {
//         printf("Preorder Iterative Traversal\n");
// 		printf ("------------------------------------\n");
// 		printf ("cmd | arg | fg\n");
// 		printf ("전위순회\n");
//         pre_traverse(pBinTree);
//         delete_tree(pBinTree);
//     }
// }
// int main() {
//     ho();
// 	system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked");
//     return 0;
// }
