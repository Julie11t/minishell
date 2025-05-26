#include "minishell.h"

char *expand_dollar(char *arg)
{
    char    *var_name;
    char    *value;

    var_name = arg + 1;
    value = NULL;
    // if(ft_strcmp(arg, "$?") == 0)
        //last exit status
    //else if (ft_strcmp(arg, "$$") == 0)
        //i dont know
    if(ft_strcmp(arg, "$0") == 0)
        return (ft_strdup("minishell"));
    else if(ft_strcmp(arg, "$") == 0)
        return (ft_strdup("$"));
    else
    {
        value = getenv(var_name);
        if(value)
            return(ft_strdup(value));
        return(ft_strdup(""));
    }
}

char *expand_double_quote(char *arg)
{
    return(arg); //i will do it later
}
char *expand_single_quote(char *arg)
{
    char *str;
    int i;
    int j;
    int len;
    
    len = ft_strlen(arg);
    i = 1;
    j = 0;
    if (len < 2)
        return (ft_strdup(""));
    str = malloc(len - 1);
    if (!str)
        return NULL;
    while (i < len - 1)
    {
        str[j++] = arg[i++];
    }
    str[j] = '\0';
    free(arg);
    return (str);
}
char    **expand(char **args)
{
    int     i;
    char *new;

    i = 0;
    new = NULL;
    while(args[i])
    {
        if(args[i][0] == '$')
        {
            new = expand_dollar(args[i]);
            free(args[i]);
            args[i] = new;
        }
        else if (args[i][0] == '\'')
            args[i] = expand_single_quote(args[i]);
        else if (args[i][0] == '"')
            args[i] = expand_double_quote(args[i]);
        i++;
    }
    return(args);
}