#include "../minishell.h"

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

// //전위순회
// parent 0null, 1<, 2>  ==> 현재'>>'이나, '<<'의 경우를 표현할수 없다.
// 지역변수 flag는 리다이렉션의 연속되면 false를 저장합니다.
void		_pre_traverse(t_tree_node *root, t_list *env, char parent)
{
	int backup_std[2];
	int flag;
	backup_std[0] = dup(0);
	backup_std[1] = dup(1);

	// pipe
	if (ft_strncmp(root->command[0], "|", 1) == 0)
	{
		ft_pipe(root, env);
	}
	// redirect
	else if(root->flag == 0)
	{
		flag = false;
		if (!(parent == root->command[0][0] && (parent == '<' || parent == '>')))
			flag = true;
		redir_out(root, root->right, flag);
		redir_in(root, root->right, flag);
		_pre_traverse(root->left, env, root->command[0][0]);
		if (!strcmp(root->command[0], "<<"))
			unlink(".heredoc");
	}
	// command
	else if(root->flag == 1)
	{
		ft_command(root, env);
	}

	dup2(backup_std[0], 0);
	dup2(backup_std[1], 1);
}


void	pre_traverse(t_tree *tree, t_list *env)
{
	t_tree_node *root;

	if (!tree)
		return ;
	root = tree->root_node;
	_pre_traverse(root, env, 0);
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


//     pReturn = create_tree();
//     if (pReturn != NULL) {
//         pNodeA = insert_root(pReturn, "A", "ㅂ", 0);

//         pNodeB = insert_left(pNodeA, "B", "ㅈ", 1);

//         pNodeC = insert_right(pNodeA,"C", "ㄷ", 2);
//         if (pNodeB != NULL) {

//             pNodeD = insert_left(pNodeB, "D", "ㄱ", 3);

//             pNodeE = insert_right(pNodeB,"E", "ㅅ", 4);
//         }
//         if (pNodeC != NULL) {

//             pNodeF = insert_left(pNodeC, "F", "ㅛ", 5);

//             pNodeG = insert_right(pNodeC, "G", "ㅕ",6);
//         }
//         if (pNodeD != NULL) {

//             pNodeH = insert_left(pNodeD, "H", "ㅑ", 7);

//             pNodeI = insert_right(pNodeD, "I", "ㅐ", 8);
//         }
//         if (pNodeE != NULL) {

//             pNodeJ = insert_left(pNodeE, "J", "ㅔ", 9);
//         }
//         if (pNodeF != NULL) {

//             pNodeK = insert_right(pNodeF, "K", "ㅁ", 10);
//         }
//         if (pNodeG != NULL) {

//             pNodeL = insert_left(pNodeG, "L", "ㄴ", 11);

//             pNodeM = insert_right(pNodeG, "M", "ㅇ", 12);
//         }
//     }

//     return pReturn;
// }


// int main() {
//     t_tree *pBinTree = NULL;
//     pBinTree = createExampleBinTree();
//     if (pBinTree != NULL) {
//         printf("Preorder Iterative Traversal\n");
// 		printf ("------------------------------------\n");
// 		printf ("cmd | arg | fg\n");
// 		printf ("전위순회\n");
//         pre_traverse(pBinTree);
// 		printf ("중위순회\n");
// 		in_traverse(pBinTree);
// 		printf ("후위순회\n");
// 		post_traverse(pBinTree);
//         delete_tree(pBinTree);
//     }
//     return 0;
// }
