/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gshim <gshim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 22:01:07 by kyujlee           #+#    #+#             */
/*   Updated: 2022/04/08 09:13:32 by gshim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sighandler(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
}

void	disable_signal(void)
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
		printf("Quit: 3\n");
}

void	set_signal(void)
{
	signal(SIGINT, sig_in_child);
	signal(SIGQUIT, sig_in_child);
}
