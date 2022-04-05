/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyujlee <kyujlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 22:01:07 by kyujlee           #+#    #+#             */
/*   Updated: 2022/04/05 22:02:17 by kyujlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_int(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("%c[K\n", 27);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sighandler(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
}

char	*ft_colorstr(char *str)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin("\033[0;32m", str);
	ret = ft_strjoin(tmp, "\x1b[0m ▶️  ");
	free(tmp);
	return (ret);
}
