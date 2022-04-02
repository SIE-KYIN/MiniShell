/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 12:17:31 by gshim             #+#    #+#             */
/*   Updated: 2021/05/03 19:43:30 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *ptr, size_t size)
{
	unsigned int	i;
	unsigned char	*arr;

	arr = (unsigned char *)ptr;
	i = 0;
	while (i < size)
	{
		arr[i] = 0;
		i++;
	}
}
