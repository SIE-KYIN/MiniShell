#include "../Inc/minishell.h"

void ft_error(int flag)
{
    if (flag == 1)
        printf ("Put correct nums of paramater");
    printf("Error");
}


char	*ft_strdup(const char *src)
{
	int		i;
	char	*str;

	i = 0;
	while (src[i] != '\0')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int envv_len(char **envv)
{
    int ret;

    ret = 0;
    while (*envv++)
    {
        ret++;
    }
    return (ret);
}

int init_envv(char **envv)
{
    int i;

    i = 0;
    g_envv = (char **)malloc(sizeof(char *) * envv_len(envv) + 1);
    while (envv[i])
    {
        g_envv[i] = ft_strdup(envv[i]);
        i++;
    }
    return (0);
}