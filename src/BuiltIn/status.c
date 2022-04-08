/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:37:34 by gshim             #+#    #+#             */
/*   Updated: 2022/04/08 02:12:14 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//WEXITSTATUS
static int	wexitstatus(int status)
{
	return (status >> 8);
}

//		0000 0000 0000 0000
//	and|0000 0000 0111 1111
// ㅎㅏ위 7개 비트가 출력된다.
static int	wstatus(int status)
{
	return (status & 0177);
}

// 하위비트를 출력했는데 0이라면 상위비트에 저장이 되었다는 뜻이고 이는 정상종료여부를 반환한다.
static bool	wifexited(int status)
{
	return (wstatus(status) == 0);
}

int	get_status(int status)
{
	if (wifexited(status))
		return (wexitstatus(status));
	else
		return (status);
}

void	set_status(t_list *env, int status)
{
	free(env->top.data);
	env->top.data = ft_itoa(status);
}
