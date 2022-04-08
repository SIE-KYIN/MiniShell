/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 09:13:12 by gshim             #+#    #+#             */
/*   Updated: 2022/04/08 09:13:41 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_colorstr(char *str)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin("\033[0;32m", str);
	ret = ft_strjoin(tmp, "\x1b[0m ▶️  ");
	free(tmp);
	return (ret);
}
