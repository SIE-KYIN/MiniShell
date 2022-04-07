/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 22:01:07 by kyujlee           #+#    #+#             */
/*   Updated: 2022/04/07 18:31:07 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	sighandler(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
}

void	disable_signal(void)	// 꺼준다.
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

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

void	sig_in_child(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	if (sig == SIGQUIT)
	{
		printf("Quit: 3<<\n");
		exit (1);
	}
}

void	set_signal()
{
	signal(SIGINT, sig_in_child);
	signal(SIGQUIT, sig_in_child);
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
