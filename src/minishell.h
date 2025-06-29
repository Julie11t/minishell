/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhasoneh <mhasoneh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:23:08 by mhasoneh          #+#    #+#             */
/*   Updated: 2025/05/26 17:23:08 by mhasoneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_ARGS 1024
# define BUFFER_SIZE 4096
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h> 

// ─────────────────────────────────────────────
// Structs
// ─────────────────────────────────────────────
typedef struct s_token
{
	char			*value;
	char			*type;
	struct s_token	*next;
}	t_token;

typedef struct s_parse_state
{
	int	i;
	int	j;
	int	k;
	int	in_single_quote;
	int	in_double_quote;
}	t_parse_state;
// ─────────────────────────────────────────────
// Tokenizer Functions
// ─────────────────────────────────────────────
void	tokenize(char **array, t_token **token);
void	create_token(t_token **token, char *value, char *type);
int		check_command(char *word);
void	free_tokens(t_token *token);
int		check_syntax_error(char **array);
// ─────────────────────────────────────────────
// Parsing and Argument Handling
// ─────────────────────────────────────────────
char	**parse_arguments(const char *input, int *arg_count);
char	*unescape_string(const char *src);
int		whileloopstring(int i, int j, int len, char *buffer,
			const char *src, int bufsize, int string);
// ─────────────────────────────────────────────
// Shell Control Functions
// ─────────────────────────────────────────────
void	shell_loop(char **envp, int argc);
void	handle_command(char *input, char **args, int arg_count,
			char **envp, t_token *token);
char	*get_input(void); //(char *buffer, size_t size) Assumed to be implemented
// ─────────────────────────────────────────────
// Command Handlers
// ─────────────────────────────────────────────
void	handle_echo_command(t_token *token);
void	handle_cat_command(char **args, char **envp);
void	handle_ls_command(char **args, char **envp);
void	handle_type_command(const char *input);
void	handle_cd_command(char *path, int arg_count);
// ─────────────────────────────────────────────
// Helpers and Utilities
// ─────────────────────────────────────────────
void	init_shell(void); // Assumed to be implemented
int		is_shell_builtin(const char *cmd); // Assumed to be implemented
void	system_handler(char *input); // Assumed to be implemented
char	**expand(char **args);
char	*print_inside_quotes(const char *src);

#endif // MINISHELL_H
