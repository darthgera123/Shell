#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include "shellFunctions.h"

/* Creates a buffer size and reads character by character */
char *read_line()
{
    int buffSize = buffer_size;
    int pos = 0;
    char *buffer;
    int run = 1;
    int c;
    buffer = new();
    if(!buffer)
    {
        fprintf(stdout,"Not enough space to run\n");
        exit(0);
    }

    while(run){
        c = getchar();
        if(c==EOF || c == '\n')
        {
            buffer[pos]='\0';
            run =0;
            return buffer;
        }
        else{
            buffer[pos] = c;
        }
        pos++;
        if(pos>=buffer_size)
        {
            buffSize += buffer_size;
            buffer = realloc(buffer,buffSize);
            if(!buffer)
            {
                fprintf(stdout,"Not enough space to run\n");
                exit(0);
            }
        }
    }
}

/* Splits the lines on the basis of space or tabs and returns an array of pointers */
char **split_line(char *line)
{
    int buffSize = TOK_BUFF_SIZE;
    int pos = 0;

    char **tokens;
    tokens = malloc(TOK_BUFF_SIZE*sizeof(char*));
    char *token;

    if(!tokens)
    {
        fprintf(stdout,"shell : allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);
    while(token !=NULL){
        tokens[pos++] = token;

        if(pos>=buffSize)
        {
            buffSize += TOK_BUFF_SIZE;
            tokens = realloc(tokens,buffSize*sizeof(char*));
            /* error handling */
            if(!tokens)
            {
                fprintf(stderr,"allocation error\n");
                exit(0);
            }
        }
        token = strtok(NULL, TOK_DELIM);
    }
    free(token);
    tokens[pos] = NULL;
    return tokens;
}
/* Splits the lines on the basis of semi colons and returns an array of pointers */
char **split_command(char *line)
{
    int buffSize = TOK_BUFF_SIZE;
    int pos = 0;

    char **tokens;
    tokens = malloc(TOK_BUFF_SIZE*sizeof(char*));
    char *token;

    if(!tokens)
    {
        fprintf(stdout,"shell : allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, COM_DELIM);
    while(token !=NULL){
        tokens[pos++] = token;

        if(pos>=buffSize)
        {
            buffSize += TOK_BUFF_SIZE;
            tokens = realloc(tokens,buffSize*sizeof(char*));
            if(!tokens)
            {
                fprintf(stderr,"allocation error\n");
                exit(0);
            }
        }
        token = strtok(NULL, COM_DELIM);
    }
    tokens[pos] = NULL;
    free(token);
    return tokens;
}