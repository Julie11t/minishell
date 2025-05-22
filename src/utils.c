#include "./lib/libft.h"

int	is_shell_builtin(const char *cmd)
{
	if (ft_strcmp(cmd, "type") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "exit") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "unset") == 0)
	{
		printf("%s is a shell builtin\n", cmd);
		return (1);
	}
	return (0);
}

void	system_handler(char *input)
{
	size_t	len;

	len = strlen(input);
	if (input[len - 1] == '\n')
		input[len - 1] = '\0';
	system(input);
}

void	print_welcome_banner(void)
{
	// printf("┏┓┳┏┓┳┳┓┏┓\n");
	// printf("┗┓┃┃┓┃┃┃┣┫\n");
	// printf("┗┛┻┗┛┛ ┗┛┗ .\n");
	// printf("			\n");
}

void	ft_putstr(const char *s)
{
	if (s)
		write(1, s, strlen(s));
}

void	ft_printf(const char *format, ...)
{
	va_list		args;
	const char	*p;

	va_start(args, format);
	p = format;
	while (*p)
	{
		if (*p == '%' && *(p + 1) == 's')
		{
			p++;
			ft_putstr(va_arg(args, char *));
		}
		else if (*p == '%' && *(p + 1) == 'c')
		{
			p++;
			ft_putchar((char)va_arg(args, int));
		}
		else
			ft_putchar(*p);
		p++;
	}
	va_end(args);
}
