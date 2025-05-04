#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>  
#include <stdbool.h> 

typedef struct s_token
{
    char *value;
    char *type;
    struct s_token *next;
}   t_token;

void    Getcwd(char *buf, size_t size);
char	**check_cmd_path(char **cmd, char **envp);
char	*get_env_path(char **envp);
char	**get_directories(char **cmd, char *path_env);
char	*check_cmd_exist(char **cmd, char *path_env);
char	*free_norm(char **ptr, char *ret);
void	ft_free(char **matrix);
char	*free_norm(char **ptr, char *ret);



