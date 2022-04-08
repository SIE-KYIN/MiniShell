/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:59:54 by gshim             #+#    #+#             */
/*   Updated: 2022/04/08 10:26:11 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_word_cnt(char const *str, char c)
{
	int	cnt;

	cnt = 0;
	while (*str)
	{
		if (!(*str == c))
		{
			++cnt;
			while (*str && !(*str == c))
				++str;
		}
		if (*str)
			++str;
	}
	return (cnt);
}

static int	len(char const *str, char c)
{
	int		len;

	len = 0;
	while (str[len] && !(str[len] == c))
		++len;
	return (len);
}

char	**ft_split_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	return (NULL);
}

static void	copy_word(char const *str, char *split, char c)
{
	int	i;

	i = 0;
	while (*str && !(*str == c))
		split[i++] = *(str++);
}

char	**ft_split(char const *str, char c)
{
	int		word_cnt;
	char	**split;
	int		i;

	if (!str)
		return (0);
	word_cnt = get_word_cnt(str, c);
	split = (char **)ft_calloc(word_cnt + 1, sizeof(char *));
	if (!split)
		return (0);
	i = 0;
	while (i < word_cnt)
	{
		if (!(*str == c))
		{
			split[i] = (char *)ft_calloc(len(str, c) + 1, sizeof(char));
			if (!split[i])
				return ((char **)ft_split_free(split));
			copy_word(str, split[i++], c);
			str += len(str, c);
		}
		++str;
	}
	return (split);
}
