/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:46:41 by gshim             #+#    #+#             */
/*   Updated: 2022/04/08 10:49:06 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_out(t_tree_node *root, t_tree_node *right, bool flag)
{
	int	fd;

	if (!ft_strcmp(root->command[0], ">"))
		fd = open(right->command[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strcmp(root->command[0], ">>"))
		fd = open(right->command[0], O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		return (0);
	if (fd == -1)
	{
		strerror(errno);
		return (-1);
	}
	if (flag)
		dup2(fd, 1);
	close(fd);
	return (0);
}

int	redir_in(t_tree_node *root, t_tree_node *right, bool flag, t_info *info)
{
	int	fd;
	(void)info;
	fd = 0;
	if (!ft_strcmp(root->command[0], "<"))
	{
		fd = open(right->command[0], O_RDONLY, 0644);
		if (fd == -1)
			return (-1);
	}
	else if (!ft_strcmp(root->command[0], "<<"))
	{
		fd = heredoc(right);
		if (fd == -1)
			return (-1);
	}
	else
		return (0);
	if (flag)
		dup2(fd, 0);
	close(fd);
	return (0);
}
