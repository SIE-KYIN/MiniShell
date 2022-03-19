#include "../minishell.h"

void ft_error(int flag)
{
    if (flag == 1)
        printf ("Put correct nums of paramater");
    printf("Error");
}

char	*ft_strndup(const char *src, int from, int to)
{
	char	*str;
    int i;

	str = (char *)malloc(sizeof(char) * (to - from + 2));
	if (!str)
		return (0);
	i = 0;
	while (from <= to)
    {
		str[i] = src[from];
        i++;
        from++;
    }
	str[i] = '\0';
	return (str);
}

int is_same(char *str1, char *str2)
{
    int i;

    i = 0;
    while (str1[i] || str2[i])
    {
        if (str1[i] != str2[i])
            return (0);
        i++;
    }
    return (1);
}

void print_intro()
{
    printf ("\033[0;34m/*******************************/\n");
    printf ("/*                             */\n");
    printf ("/*   \x1b[0m       :::      :::::::: \033[0;34m */\n");
    printf ("/*  \x1b[0m      :+:      :+:    :+: \033[0;34m */\n");
    printf ("/*   \x1b[0m   +:+ +:+         +:+   \033[0;34m */\n");
    printf ("/*  \x1b[0m  +#+  +:+       +#+      \033[0;34m */\n");
    printf ("/*  \x1b[0m #+#+#+#+#+   +#+         \033[0;34m */\n");
    printf ("/*   \x1b[0m    #+#    #+#           \033[0;34m */\n");
    printf ("/*   \x1b[0m   ###   ########.kr     \033[0;34m */\n");
    printf ("/*                             */\n");
    printf ("/*         \x1b[0m    @kyujlee @gshim \033[0;34m*/\n");
    printf ("/*******************************/\n\n");
}
