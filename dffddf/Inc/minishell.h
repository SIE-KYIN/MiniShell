#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
char    **g_envv;


/*
** ms_utils.c
*/

int envv_len(char **envv);
char	*ft_strdup(const char *src);
void ft_error(int flag);
int init_envv(char **envv);