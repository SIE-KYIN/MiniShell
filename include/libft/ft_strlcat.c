/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:12:08 by gshim             #+#    #+#             */
/*   Updated: 2021/07/26 19:22:23 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	i;

	srclen = (size_t)ft_strlen((char *)src);
	if (!dest && size == 0)
		return (srclen);
	destlen = (size_t)ft_strlen(dest);
	if (size < destlen)
		return (srclen + size);
	i = 0;
	while (i < srclen && i + destlen + 1 < size)
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (destlen + srclen);
}
