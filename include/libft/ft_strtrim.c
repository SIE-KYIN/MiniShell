/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:49:54 by gshim             #+#    #+#             */
/*   Updated: 2021/07/26 19:20:11 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char c, char const *set)
{
	while (*set != '\0')
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*ret;

	if (!s1 || !set)
		return (0);
	i = 0;
	while (isset(s1[i], set) && s1[i] != '\0')
		i++;
	j = ft_strlen(s1) - 1;
	while (j >= 0)
	{
		if (isset(s1[j], set))
			j--;
		else
			break ;
	}
	if (i > j)
		return (ft_strdup(""));
	ret = (char *)malloc(sizeof(char) * (j - i + 2));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1 + i, (size_t)(j - i + 1 + 1));
	return (ret);
}
