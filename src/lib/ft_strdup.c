#include "libft.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	i;

	i = ft_strlen(s);
	dup = (char *)malloc(i * sizeof(char) + 1);
	if (!dup)
	{
		free(dup);
		dup = NULL;
		return (0);
	}
	i = 0;
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_free(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

char	*path_join(const char *dir, const char *file)
{
	char	*joined;
	size_t	len_dir;
	size_t	len_file;
	size_t	i;
	size_t	j;

	len_dir = ft_strlen(dir);
	len_file = ft_strlen(file);
	joined = (char *)malloc((len_dir + 1) + (len_file + 1));
	if (!joined)
		ft_free(&joined);
	i = -1;
	while (++i < len_dir)
		joined[i] = dir[i];
	joined[i++] = '/';
	j = -1;
	while (j < len_file)
		joined[++i] = file[++j];
	joined[i] = '\0';
	return (joined);
}
