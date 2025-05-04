#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>  
#include "libft/libft.h"

typedef struct s_token
{
    char *value;
    char *type;
    struct s_token *next;
} t_token;

void create_token(t_token **token, char *value, char *type)
{
    t_token *new;
    t_token *temp;

    new = malloc(sizeof(t_token));
    if (!new)
        return;
    new->value = ft_strdup(value);
    new->type = ft_strdup(type);
    new->next = NULL;

    if (!*token)
        *token = new;
    else
    {
        temp = *token;
        while (temp->next)
            temp = temp->next;
        temp->next = new;
    }
}

void error(char *str, char *line, char **array)
{
    int i;

    i = 0;
    if (line)
        free(line);
    if (array)
    {
        while (array[i])
        {
            free(array[i]);
            i++;
        }
        free(array);
    }
    printf("%s", str);
    exit(1);
}

int count_words(char *line)
{
    int i;
    int words;

    i = 0;
    while (isspace(line[i]))
        i++;
    if (!line[i])
        error("Command not found", line, NULL); // handle empty line right here!
    words = 1;
    while (line[i])
    {
        if (isspace(line[i]))
        {
            words++;
            while (isspace(line[i]))
                i++;
        }
        if (line[i] == '\'' || line[i] == '\"')
        {
            while (line[i] != '\'' && line[i] != '\"')
                i++;
        }
        i++;
    }
    return (words);
}

void handle_quotes(char *line) //norm (26 lines)
{
    int i;
    char flag;

    i = 0;
    flag = 1;
    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '\"')
        {
            flag = line[i];
            while (line[i])
            {
                i++;
                if (line[i] == flag)
                {
                    flag = 1;
                    break;
                }
                if (line[i] == '\\')
                    i++;
            }
        }
        i++;
    }
    if (flag != 1)
        error("Command not found", line, NULL);
}

int count_current_word(char *line, int i)
{
    int count;

    count = 0;
    while (line[i] && !isspace(line[i]))
    {
        i++;
        count++;
    }
    return (count);
}

int quotes_handler(char *line, int i)
{
    while (line[i])
    {
        if (line[i] == '\'' || line[i] == '\"')
            return (++i);
        if (line[i] == '\\')
            i++;
        i++;
    }
    return (0);
}

char **split_line(char *line, char **array)
{
    int i = 0;
    int j = 0;

    while (line[i])
    {
        if (!isspace(line[i]))
        {
            if (line[i] == '\"' || line[i] == '\'')
                i = quotes_handler(line, i);

            int word_len = count_current_word(line, i);
            array[j] = malloc(word_len + 1);
            if (!array[j])
                error("malloc failed", line, array);

            strncpy(array[j], &line[i], word_len); //code ft_strncpy
            array[j][word_len] = '\0';
            j++;
            i += word_len;
        }
        i++;
    }
    array[j] = NULL;
    return (array);
}

int check_command(char *word)
{
    if (ft_strcmp(word, "echo") == 0 || ft_strcmp(word, "cd") == 0 ||
        ft_strcmp(word, "pwd") == 0 || ft_strcmp(word, "export") == 0 ||
        ft_strcmp(word, "unset") == 0 || ft_strcmp(word, "env") == 0 ||
        ft_strcmp(word, "exit") == 0)
        return (1);
    return (0);
}

void tokenize(char **array, t_token **token)
{
    int i;

    i = 0;
    while (array[i])
    {
        if (check_command(array[i]))
            create_token(token, array[i], "built in");
        else if (strcmp(array[i], "|") == 0)
            create_token(token, "|", "pipe");
        else if (strcmp(array[i], "<") == 0)
            create_token(token, array[++i], "redirect input");
        else if (strcmp(array[i], ">") == 0)
            create_token(token, array[++i], "redirect output");
        else if (strcmp(array[i], ">>") == 0)
            create_token(token, array[++i], "append output");
        else if (strcmp(array[i], "<<") == 0)
            create_token(token, array[++i], "here-document");
        else
            create_token(token, array[i], "word");
        i++;
    }
}

void tokenizer(char *line, t_token **token)
{
    char **array;
    int words;
    int i;

    words = 0;
    i = 0;
    handle_quotes(line);
    words = count_words(line);
    array = malloc(sizeof(char *) * (words + 1));
    if (!array)
    {
        free(line);
        exit(1);
    }
    array = split_line(line, array);
    tokenize(array, token);
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

void print_tokens(t_token *token)
{
    while (token)
    {
        printf("type: %s value: %s\n", token->type, token->value);
        token = token->next;
    }
}

int     main(int argc, char *argv[])
{
    char    *read;
    t_token     *token;

    token = NULL;
    (void)argc;
    (void)argv;
    read = readline("minishell > ");
    add_history(read);
    tokenizer(read, &token);
    print_tokens(token);
    free(read); //ig?
    return (0);
}

//main without readline or add_history
// int     main(int argc, char *argv[])
// {
//     char    *read;
//     t_token     *token;

//     token = NULL;
//     (void)argc;
//     read = strdup(argv[1]);
//     tokenizer(read, &token);
//     print_tokens(token);
//     return (0);
// }
