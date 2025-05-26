#include "minishell.h"

// #include "libft.h"
////// LATEST
// Copies characters from src to buffer, interpreting escape sequences if inside a quoted string.
int		whileloopstring(int i, int j, int len, char *buffer, const char *src, int bufsize, int string)
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
	return j;
}
// Removes surrounding quotes and processes escape sequences in a string.
char	*unescape_string(const char *src)
{
	static char	buffer[1024];
	char		*processed;
	int			i;
	int			j;
	size_t		len;
	int			string;

	processed = buffer;
	i = 0;
	j = 0;
	string = 0;
	len = ft_strlen(src);
	if (len >= 2 && ((src[0] == '\'' && src[len - 1] == '\'') || (src[0] == '"' && src[len - 1] == '"')))
	{
		src++;
		len -= 2;
		string = 1;
	}
	j = whileloopstring(i, j, len, buffer, src, sizeof(buffer), string);
	return (processed);
}
// Counts the number of single and double quotes in the input string.
void	count_quotes(const char *input, int *singleq, int *doubleq)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			(*singleq)++;
		else if (input[i] == '"')
			(*doubleq)++;
		i++;
	}
}
// Splits the input line into arguments while respecting quotes and escape characters.
char **parse_arguments(const char *input, int *arg_count, int *quote_error)
{
	static char *argv[64];
	char buffer[1024];
	int in_single_quote = 0;
	int in_double_quote = 0;
	int i = 0, j = 0, k = 0;
	char c;

	while (input[i])
	{
		c = input[i];
		if (c == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			buffer[j++] = input[i++];
			continue;
		}
		if (c == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			buffer[j++] = input[i++];
			continue;
		}
		if (!in_single_quote && !in_double_quote && (c == ' ' || c == '\t'))
		{
			if (j > 0)
			{
				buffer[j] = '\0';
				argv[k++] = ft_strdup(buffer);
				j = 0;
			}
			i++;
			continue;
		}
		if (c == '\\' && input[i + 1])
		{
			buffer[j++] = input[++i];
			i++;
			continue;
		}
		buffer[j++] = input[i++];
	}
	if (j > 0)
	{
		buffer[j] = '\0';
		argv[k++] = ft_strdup(buffer);
	}
	argv[k] = NULL;
	*arg_count = k;
	*quote_error = in_single_quote || in_double_quote;
	return argv;
}

// void print_tokens(t_token *token)
// {
//     t_token *temp;

//     while (token)
//     {
//         printf("type: %s value: %s\n", token->type, token->value);
//         temp = token;
//         token = token->next;
//         free(temp->value);
//         free(temp->type);
//         free(temp);
//     }
// }

// void print_argv(char **argv)
// {
//     int i = 0;

//     printf("Arguments:\n");
//     while (argv[i])
//     {
//         printf("[%d]: %s\n", i, argv[i]);
//         i++;
//     }
// }


// Runs the main shell loop that reads user input, parses it, and executes commands.
void	shell_loop(char **envp)
{
	char	input[1024];
	int		arg_count;
	int		quote_error;
	int		singleq;
	int		doubleq;
	char	**args;
	t_token		*token;

	quote_error = 0;
	singleq = 0;
	doubleq = 0;
	while (1)
	{
		token = NULL;
		prompt();
		if (get_input(input, sizeof(input)) <= 0)
		{
			printf("\n");
			break ;
		}
		count_quotes(input, &singleq, &doubleq);
		args = parse_arguments(input, &arg_count, &quote_error);
		//print_argv(args);
		if (quote_error)
		{
			printf("Unmatched quote detected!\n");
			continue ;
		}
		if (arg_count == 0)
			continue ;
		if (check_syntax_error(args))
    		continue;
		args = expand(args);
		tokenize(args, &token);
		handle_command(input, args, arg_count, envp, token);
	}
}


int	main(int argc, char **argv, char **envp)
{	
	(void)argc;
	(void)argv;
	init_shell();
	shell_loop(envp);
	return (0);
}
