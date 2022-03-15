/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:23:40 by gshim             #+#    #+#             */
/*   Updated: 2021/07/26 22:14:17 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	recursive(long long n)
{
	if (n == 0)
		return (0);
	return (1 + recursive(n / 10));
}

static int	getbuf(long long n, char **ret)
{
	int		len;

	if (n < 0)
		len = recursive(-1 * n) + 1;
	else if (n == 0)
		len = 1;
	else
		len = recursive(n);
	*ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!(*ret))
		return (-1);
	(*ret)[len] = '\0';
	return (len);
}

char	*ft_itoa(int n)
{
	int			len;
	long long	number;
	char		*ret;

	number = (long long)n;
	len = getbuf(number, &ret);
	if (len == -1)
		return (0);
	if (n < 0)
		number *= -1;
	while (--len >= 0)
	{
		ret[len] = (int)(number % 10) + '0';
		number /= 10;
	}
	if (n < 0)
		ret[0] = '-';
	return (ret);
}
