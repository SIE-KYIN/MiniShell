/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyujlee <kyujlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 22:39:05 by kyujlee           #+#    #+#             */
/*   Updated: 2022/04/05 22:39:17 by kyujlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_token_to_tree(t_tree_node *parent, char **token, int token_loc)
{
	char	**tmp;
	int		deli_loc;

	deli_loc = is_there_delimiter(token);
	if (!deli_loc)
	{
		tmp = find_cmd(token[0]);
		insert_left(parent, tmp, COMMON_BUILTIN);
		tmp = find_cmd(token[2]);
		insert_right(parent, tmp, COMMON_BUILTIN);
		return ;
	}
	tmp = find_cmd(token[token_loc]);
	insert_right(parent, tmp, -1);
	tmp = (char **)malloc(sizeof(char *) * 2);
	tmp[0] = ft_strdup(token[deli_loc]);
	tmp[1] = 0;
	insert_left(parent, tmp, DELIMITER);
	free(token[deli_loc]);
	token[deli_loc] = NULL;
	_token_to_tree(parent->left, token, token_loc - 2);
}

void	token_to_tree(t_tree *token_tree, char **token)
{
	int		deli_loc;
	int		token_loc;
	char	**tmp;

	deli_loc = is_there_delimiter(token);
	token_loc = get_latest_token_loc(token);
	if (deli_loc)
	{
		tmp = (char **)malloc(sizeof(char *) * 2);
		tmp[0] = ft_strdup(token[deli_loc]);
		tmp[1] = 0;
		insert_root(token_tree, tmp, DELIMITER);
		free(token[deli_loc]);
		token[deli_loc] = NULL;
		_token_to_tree(token_tree->root_node, token, token_loc);
	}
	else
	{
		tmp = find_cmd(token[0]);
		insert_root(token_tree, tmp, COMMON_BUILTIN);
	}
}

t_tree	*tokenize(char *line, t_list *env_list)
{
	t_tree	*token_tree;
	char	**token;

	token_tree = create_tree();
	token = ft_ms_split(line, env_list);
	token_to_tree(token_tree, token);
	free(token);
	return (token_tree);
}
