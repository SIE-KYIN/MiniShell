/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:35:07 by gshim             #+#    #+#             */
/*   Updated: 2022/03/26 21:36:31 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *dest, char *src)
{
	int	destlen;
	int	i;

	destlen = ft_strlen(dest);
	i = 0;
	while (src[i] != '\0')
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1size;
	int		s2size;
	char	*ret;

	if (!s1 || !s2)
		return (0);
	s1size = ft_strlen(s1);
	s2size = ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (s1size + s2size + 1));
	if (!ret)
		return (0);
	ret[0] = '\0';
	ft_strcat(ret, (char *)s1);
	ft_strcat(ret, (char *)s2);
	return (ret);
}

char	*ft_strjoin_3(char const *s1, char const *s2, char const *s3)
{
	int		s1size;
	int		s2size;
	int		s3size;
	char	*ret;

	if (!s1 || !s2 || !s3)
		return (0);
	s1size = ft_strlen(s1);
	s2size = ft_strlen(s2);
	s3size = ft_strlen(s3);
	ret = (char *)malloc(sizeof(char) * (s1size + s2size + s3size + 1));
	if (!ret)
		return (0);
	ret[0] = '\0';
	ft_strcat(ret, (char *)s1);
	ft_strcat(ret, (char *)s2);
	ft_strcat(ret, (char *)s3);
	return (ret);
}
