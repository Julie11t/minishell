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

//free everything and exit
void error(char *str, char *line, char **array, t_token *token)
{
    int i;
    t_token *temp;

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
    while (token)
    {
        temp = token;
        token = token->next;
        free(temp->value);
        free(temp->type);
        free(temp);
    }
    printf("%s", str);
    exit(1);
}

//count the number of words for malloc
int count_words(char *line, t_token *token)
{
    int i;
    int words;

    i = 0;
    while (isspace(line[i]))
        i++;
    if (!line[i])
        error("empty line\n", line, NULL, token);
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

//checks if the quotes are correct
void     handle_quotes(char *line, t_token *token) //26 lines
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
        error("Command not found\n", line, NULL, token);
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
    char quote;

    quote = line[i];
    i++;
    while (line[i])
    {
        if (line[i] == '\\' && line[i + 1])
            i += 2;
        else if (line[i] == quote)
            return i + 1;
        else
            i++;
    }
    return (i);
}
//splits the line based on spaces and quotes to a 2D array
char    **split_line(char *line, char **array, t_token *token) //norm !!!!!!!!!!!!!!!
{
    int i = 0;
    int j = 0;

    while (line[i])
    {
        if (!isspace(line[i]))
        {
            int start = i;
            if (line[i] == '\"' || line[i] == '\'')
                i = quotes_handler(line, i);
            else
            {
                int word_len = count_current_word(line, i);
                i += word_len;
            }
            int word_len = i - start;
            array[j] = malloc(word_len + 1);
            if (!array[j])
                error("malloc failed", line, array, token);
            strncpy(array[j], &line[start], word_len);
            array[j][word_len] = '\0';
            j++;
        }
        i++;
    }
    array[j] = NULL;
    return (array);
}

//norm :)
int check_command(char *word)
{
    if (ft_strcmp(word, "echo") == 0 || ft_strcmp(word, "cd") == 0 ||
        ft_strcmp(word, "pwd") == 0 || ft_strcmp(word, "export") == 0 ||
        ft_strcmp(word, "unset") == 0 || ft_strcmp(word, "env") == 0 ||
        ft_strcmp(word, "exit") == 0)
        return (1);
    return (0);
}

//identify each token's value
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

//main tokenizer (line -> 2D array -> linked list of tokens)
void tokenizer(char *line, t_token **token)
{
    char **array;
    int words;
    int i;

    words = 0;
    i = 0;
    handle_quotes(line, *token);
    words = count_words(line, *token);
    array = malloc(sizeof(char *) * (words + 1));
    if (!array)
    {
        free(line);
        exit(1);
    }
    array = split_line(line, array, *token);
    tokenize(array, token);
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

//for testing
void print_tokens(t_token *token)
{
    t_token *temp;

    while (token)
    {
        printf("type: %s value: %s\n", token->type, token->value);
        temp = token;
        token = token->next;
        free(temp->value);
        free(temp->type);
        free(temp);
    }
}

int main(int argc, char *argv[])
{
    char *line;
    t_token *token;

    token = NULL;
    (void)argc;
    (void)argv;
    line = readline("minishell > "); //I think readline cause extra memory leaks idk how to handle them
    add_history(line);
    tokenizer(line, &token);
    print_tokens(token);
    free(line);
    return (0);
}
