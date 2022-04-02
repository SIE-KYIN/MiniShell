/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 12:20:49 by gshim             #+#    #+#             */
/*   Updated: 2021/05/10 19:40:00 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t num)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	if (dest == source)
		return (dest);
	d = (unsigned char *)dest;
	s = (unsigned char *)source;
	i = 0;
	while (i < num)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
