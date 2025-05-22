#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef struct s_parse_state
{
	int	i;
	int	j;
	int	k;
	int	in_single_quote;
	int	in_double_quote;
}	t_parse_state;

/* input.c */
void		handle_command(char *input, char **args,
				int arg_count, char **envp);
char		*get_input(void);

void		handle_echo_command(char **args, int arg_count);
char		*unescape_string(const char *src);
char		**prepare_exec_args(char **args, int arg_count);
void		handle_ls_command(char **args, char **envp);
void		handle_cat_command(char **args, char **envp);
void		handle_type_command(const char *input);
void		handle_cd_command(char *path);

/* Utils.c */
int			is_shell_builtin(const char *cmd);
void		system_handler(char *input);
void		print_welcome_banner(void);

/*** lib ***/
/* Ft_strtok.c */
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strtok(char *str, const char *delim);

/* Strdup.c */
char		*ft_strdup(const char *s);
char		*path_join(const char *dir, const char *file);
char		*ft_free(char **ptr);

/* Ft_printf.c */
void		ft_printf(const char *format, ...);
void		ft_putstr(const char *s);
void		ft_putchar(char c);

#endif