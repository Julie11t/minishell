#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	ch;

	ch = c;
	i = ft_strlen(s);
	if (ch == '\0')
		return ((char *)(s) + i);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
			return ((char *)(s) + i);
		i++;
	}
	return (0);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*save;
	char		*token;
	int			i;

	i = 0;
	if (str)
		save = str;
	if (!save || *save == '\0')
		return (NULL);
	while (*save && ft_strchr(delim, *save))
		save++;
	if (*save == '\0')
		return (NULL);
	token = save;
	while (save[i] && !ft_strchr(delim, save[i]))
		i++;
	if (save[i])
	{
		save[i] = '\0';
		save = &save[i + 1];
	}
	else
		save = NULL;
	return (token);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}
