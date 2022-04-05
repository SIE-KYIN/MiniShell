/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:18:08 by gshim             #+#    #+#             */
/*   Updated: 2022/04/04 21:18:24 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void _token_to_tree(t_tree_node *parent, char **token, int token_loc, int token_cnt)
{
    char **tmp;
    int deli_loc;

    deli_loc = is_there_delimiter(token, token_cnt);
    if (!deli_loc)
    {
        tmp = find_cmd(token[0], 0);
        insert_left(parent, tmp, COMMON_BUILTIN);
        tmp = find_cmd(token[2],0);
        insert_right(parent, tmp, COMMON_BUILTIN);
        return ;
    }
    tmp = find_cmd(token[token_loc], 0);
    insert_right(parent, tmp, -1);
    tmp = (char **)malloc(sizeof(char *) * 2);
    tmp[0] = ft_strdup(token[deli_loc]);
    tmp[1] = 0;
    insert_left(parent, tmp, DELIMITER);
    // free(token[deli_loc]);
    token[deli_loc] = NULL;
    _token_to_tree(parent->left, token, token_loc + 2, token_cnt);
}

void token_to_tree(t_tree *token_tree, char **token)
{
    int deli_loc;
    int token_cnt1;
    char **tmp;
	token_cnt1 = token_cnt(token);
    deli_loc = is_there_delimiter(token, token_cnt1);

    if (deli_loc)
    {
        tmp = (char **)malloc(sizeof(char *) * 2);
        tmp[0] = ft_strdup(token[deli_loc]);
        tmp[1] = 0;
        insert_root(token_tree, tmp, DELIMITER);
        // free(token[deli_loc]);
        token[deli_loc] = NULL;
        _token_to_tree(token_tree->root_node, token, 0,token_cnt1);
    }
    else
    {
        tmp = find_cmd(token[0], 0);
        insert_root(token_tree, tmp, COMMON_BUILTIN);
    }
}

void parse_redirection()
{

}

void parse_heredoc()
{

}

void parse_pipe()
{

}

void parse_tree(t_tree *tree, char *line)
{
	char *s;

	while (ft_strchr(line, '|') - line <= 0) // line에 '|'가 있다면
	{
		insert
	}
}

t_tree *tokenize2(char *line, t_list *env_list)
{
    t_tree *token_tree;
    char **token;

    token_tree = create_tree();

	parse_tree(token_tree, line);

    return (token_tree);
}
