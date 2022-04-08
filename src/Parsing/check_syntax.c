/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyujlee <kyujlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 22:24:45 by kyujlee           #+#    #+#             */
/*   Updated: 2022/04/05 22:29:04 by kyujlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_s_c(char c)
{
	(void)c;
	if (c == ';')
		return (0);
	return (1);
}

int	is_empty_str(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	is_opened_quotes(char *line)
{
	char	curr_quote;
	int		i;

	i = -1;
	curr_quote = 0;
	while (line[++i])
	{
		if (!curr_quote && (line[i] == '\'' || line[i] == '"'))
		{
			if (i == 0 || line[i - 1] != '\\')
				curr_quote = line[i];
		}
		else if (curr_quote && line[i - 1] != '\\' && line[i] == curr_quote)
			curr_quote = 0;
	}
	return (curr_quote);
}

int	is_valid_location(char *line)
{
	int	i;

	i = -1;
	if (line[0] == '|')
		return (0);
	i = ft_strlen(line);
	while (line[--i])
	{
		if (line[i] == ' ')
			continue ;
		else if (line[i] == '>' || line[i] == '<'
			|| line[i] == '|')
			return (0);
		else
			break ;
	}
	return (1);
}

int	check_syntax(char *line)
{
	if (!is_empty_str(line))
	{
		free(line);
		return (0);
	}
	if (!is_valid_location(line))
	{
		ft_error(3);
		free(line);
		return (0);
	}
	if (is_opened_quotes(line))
	{
		ft_error(4);
		free(line);
		return (0);
	}
	return (1);
}
