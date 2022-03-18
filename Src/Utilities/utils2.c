#include "../../Inc/minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (!dst && !src)
		return ((void *)0);
	while (n-- > 0)
		*((unsigned char *)dst + n) = *((unsigned char *)src + n);
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_1;
	size_t	len_2;
	char	*ret;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	if ((ret = (char *)malloc(len_1 + len_2 + 1)) == 0)
		return (0);
	*(ret + len_1 + len_2) = 0;
	ft_memcpy(ret, s1, len_1);
	ft_memcpy(ret + len_1, s2, len_2);
	return (ret);
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
