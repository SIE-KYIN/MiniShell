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

char *ft_colorstr(char *str)
{
    char *ret;
    char *tmp;

    tmp = ft_strjoin("\033[0;32m", str);
    ret = ft_strjoin(tmp, "\x1b[0m ▶️  ");
    free(tmp);
    return (ret);
}
