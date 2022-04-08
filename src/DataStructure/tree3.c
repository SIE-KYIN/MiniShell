/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 09:14:47 by gshim             #+#    #+#             */
/*   Updated: 2022/04/08 09:15:46 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_redirect(char *command)
{
	if (!ft_strcmp(command, ">") || !ft_strcmp(command, ">>")
		|| !ft_strcmp(command, "<") || !ft_strcmp(command, "<<"))
		return (true);
	else
		return (false);
}

void	_pre_traverse(t_tree_node *root, t_list *env, char parent)
{
	int	backup_std[2];
	int	flag;

	backup_std[0] = dup(0);
	backup_std[1] = dup(1);
	if (ft_strcmp(root->command[0], "|") == 0)
		ft_pipe(root, env);
	else if (is_redirect(root->command[0]))
	{
		flag = false;
		if (!(parent == root->command[0][0]
			&& (parent == '<' || parent == '>')))
			flag = true;
		if (redir_out(root, root->right, flag) != -1)
			if (redir_in(root, root->right, flag) != -1)
				_pre_traverse(root->left, env, root->command[0][0]);
		if (!ft_strcmp(root->command[0], "<<"))
			unlink(".heredoc");
	}
	else
		ft_command(root, env);
	dup2(backup_std[0], 0);
	dup2(backup_std[1], 1);
}

void	pre_traverse(t_tree *tree, t_list *env)
{
	t_tree_node	*root;

	if (!tree)
		return ;
	root = tree->root_node;
	_pre_traverse(root, env, 0);
}
