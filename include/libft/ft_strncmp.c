/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:28:29 by gshim             #+#    #+#             */
/*   Updated: 2021/05/11 16:54:24 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	i = 0;
	while (a[i] != '\0' || b[i] != '\0')
	{
		if (i == n)
			break ;
		if (a[i] < b[i])
			return (-1);
		else if (a[i] > b[i])
			return (1);
		i++;
	}
	return (0);
}
