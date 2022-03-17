#include "../../Inc/minishell.h"

void sig_int(int sig)
{
    rl_on_new_line();
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void sigHandler()
{
    signal(SIGINT, sig_int);
    signal(SIGQUIT, SIG_IGN);
}