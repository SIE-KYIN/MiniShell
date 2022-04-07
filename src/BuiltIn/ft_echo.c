/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:35:26 by gshim             #+#    #+#             */
/*   Updated: 2022/04/06 18:21:19 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// -뒤로 옵션에 해당하지 않는 문자가 있으면 옵션으로 취급하지 않습니다.
static bool	check_option(char *str, char *option)
{
	size_t	len;
	size_t	i;

	if (!str)
		return (false);
	if (str[0] != '-')
		return (false);
	len = ft_strlen(str);
	i = 0;
	while (++i < len)
	{
		if (ft_strchr(option, str[i]) == NULL)
			return (false);
	}
	return (true);
}

// -n
int	ft_echo(char *argv[])
{
	int	i;
	int	flag;

	flag = 1;
	while (check_option(argv[flag], "n"))
		flag++;
	i = flag;
	while (argv[i])
	{
		if (i != flag)
			printf(" ");
		printf("%s", argv[i]);
		i++;
	}
	if (flag == 1)
		printf("\n");
	return (0);
}
