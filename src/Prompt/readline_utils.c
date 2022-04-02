#include "../minishell.h"

void sig_int(int sig)
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

void sigHandler()
{
    signal(SIGINT, sig_int);
    signal(SIGQUIT, SIG_IGN);
}

void	sig_in_child(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	if (sig == SIGQUIT)
		printf("Quit: 3\n");
}

void	set_signal()
{
	signal(SIGINT, sig_in_child);
	signal(SIGQUIT, sig_in_child);
}

void	disable_signal()
{
	signal(SIGINT, SIG_IGN);
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
