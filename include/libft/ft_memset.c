/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 12:01:43 by gshim             #+#    #+#             */
/*   Updated: 2021/05/03 19:05:13 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned int	i;
	unsigned char	*arr;

	arr = (unsigned char *)ptr;
	i = 0;
	while (i < num)
	{
		arr[i] = value;
		i++;
	}
	return (ptr);
}
