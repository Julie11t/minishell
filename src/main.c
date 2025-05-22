#include "./lib/libft.h"

// #include "libft.h"
////// LATEST
// Copies characters from src to buffer, 
// interpreting escape sequences if inside a quoted string.
int	whileloopstring(int i, int j, int len, char *buffer,
			const char *src, int bufsize, int string)
{
	while (i < len && j < bufsize - 1)
	{
		if (src[i] == '\\' && i + 1 < len)
		{
			if (string && src[i + 1] == 'n')
				buffer[j++] = '\n';
			else if (src[i] == 't')
				buffer[j++] = '\t';
			else if (src[i] == '\\')
				buffer[j++] = '\\';
			else if (src[i] == '"')
				buffer[j++] = '"';
			else if (src[i] == '\'')
				buffer[j++] = '\'';
			else
				buffer[j++] = src[i];
			i++;
		}
		else
			buffer[j++] = src[i++];
	}
	buffer[j] = '\0';
	return (j);
}

// Removes surrounding quotes and processes escape sequences in a string.
char	*unescape_string(const char *src)
{
	static char	buffer[1024];
	int			i;
	int			j;
	size_t		len;
	int			string;

	i = 0;
	j = 0;
	string = 0;
	len = ft_strlen(src);
	if (len >= 2 && ((src[0] == '\'' && src[len - 1] == '\'')
			|| (src[0] == '"' && src[len - 1] == '"')))
	{
		src++;
		len -= 2;
		string = 1;
	}
	j = whileloopstring(i, j, len, buffer, src, sizeof(buffer), string);
	return (buffer);
}

void	nully(struct s_parse_state *s)
{
	s->i = 0;
	s->j = 0;
	s->k = 0;
	s->in_single_quote = 0;
	s->in_double_quote = 0;
}


// Splits the input line into arguments
// while respecting quotes and escape characters.
char	**parse_arguments(const char *input, int *arg_count, int *quote_error)
{
	struct s_parse_state	s = {0};
	static char				*argv[64];
	char					buffer[1024];
	char					c;

	nully(&s);
	while (input[s.i])
	{
		c = input[s.i];
		if (c == '\'' && !s.in_double_quote)
		{
			s.in_single_quote = !s.in_single_quote;
			s.i++;
			continue ;
		}
		if (c == '"' && !s.in_single_quote)
		{
			s.in_double_quote = !s.in_double_quote;
			s.i++;
			continue ;
		}
		if (!s.in_single_quote && !s.in_double_quote && (c == ' ' || c == '\t'))
		{
			if (s.j > 0)
			{
				buffer[s.j] = '\0';
				argv[s.k++] = ft_strdup(buffer);
				s.j = 0;
			}
			s.i++;
			continue ;
		}
		if (c == '\\' && input[s.i + 1])
		{
			if (input[s.i] == '\\')
				s.i++;
			buffer[s.j++] = input[s.i++];
			continue ;
		}
		buffer[s.j++] = c;
		s.i++;
	}
	if (s.j > 0)
	{
		buffer[s.j] = '\0';
		argv[s.k++] = ft_strdup(buffer);
	}
	argv[s.k] = NULL;
	*arg_count = s.k;
	*quote_error = s.in_single_quote || s.in_double_quote;
	return (argv);
}

// Runs the main shell loop that reads user input, parses it, and executes commands.
void	shell_loop(char **envp, int arg_count)
{
	char	*input;
	char	**args;
	int		quote_error;

	quote_error = 0;
	while (1)
	{
		input = get_input();
		if (input == NULL)
			break ;
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		args = parse_arguments(input, &arg_count, &quote_error);
		if (quote_error)
		{
			printf("Syntax Error!\n");
			free(input);
			continue ;
		}
		handle_command(input, args, arg_count, envp);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	print_welcome_banner();
	shell_loop(envp, argc);
	rl_clear_history();
	return (0);
}
