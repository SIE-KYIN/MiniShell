/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyujlee <kyujlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 22:49:11 by kyujlee           #+#    #+#             */
/*   Updated: 2022/04/05 23:00:48 by kyujlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_delimiter(char c, char next)
{
	if (c == '>')
	{
		if (next == '>')
			return (2);
		return (1);
	}
	if (c == '<')
	{
		if (next == '<')
			return (2);
		return (1);
	}
	if (c == '|')
		return (1);
	return (0);
}

int	cnt_delimiter(char *line)
{
	int	ret;
	int	tmp;

	ret = 0;
	while (*line)
	{
		tmp = is_delimiter(*line, *(line + 1));
		if (tmp)
		{
			line += tmp;
			ret++;
		}
		else
			line++;
	}
	return (ret);
}

void	change_str(t_list *env_list, char **line, int fst, int sec)
{
	int		tmp;
	char	*fst_str;
	char	*sec_str;
	char	*thd_str;
	char	*free_ptr;

	fst_str = ft_strndup(*line, 0, fst - 1);
	sec_str = ft_strndup(*line, fst + 1, sec - 1);
	thd_str = ft_strndup(*line, sec, ft_strlen(*line) - 1);
	tmp = get_position(env_list, sec_str);
	free(sec_str);
	if (tmp == -1)
		sec_str = ft_emptystr();
	else
		sec_str = ft_strdup(get_node(env_list, tmp)->data);
	free_ptr = ft_strjoin(fst_str, sec_str);
	free(*line);
	*line = ft_strjoin(free_ptr, thd_str);
	free(free_ptr);
	free(fst_str);
	free(sec_str);
	free(thd_str);
}

int	strcnt_double_ptr(char **ret)
{
	int	i;

	i = 0;
	while (ret[i])
		i++;
	return (i);
}

char	*ft_emptystr(void)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) + 1);
	if (ret == NULL)
		return (NULL);
	ret[0] = '\0';
	return (ret);
}
