#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "shellFunctions.h"

int delete(char **a,int p,int i)
{
  for(int j=i;j<p-1;j++)
  {
    a[p] = a[p+1];
  }
  a[p]=NULL;
  p=p-1;
  return p;
}
int isAppend(char **args){
    int i=0;
    while(args[i]!=NULL)
    {
        if(strcmp(args[i],">>")==0)
        {
            return 1;
        }
        i++;
    }
    return 0;
}
char *input_file(char **args){
    int i=0;
    while(args[i]!=NULL)
    {
        if(strcmp(args[i],"<")==0)
        {
            return args[i+1];
        }
        i++;
    }
    return NULL;
}
char *output_file(char **args){
    int i=0;
    while(args[i]!=NULL)
    {
        if((strcmp(args[i],">")==0)||strcmp(args[i],">>")==0)
        {
            return args[i+1];
        }
        i++;
    }
    return NULL;
}

int countToken(char **args){
    int i=0;
    while(args[i]!=NULL){
        i++;
    }
    return i;
}
char **modify_token(char **tokens,int pos){
    int *elements = (int*)malloc(sizeof(int)*TOK_BUFF_SIZE);
    int j=0;
    for(int i=0;i<pos;i++)
    {
        if((strcmp(tokens[i],">")==0)||(strcmp(tokens[i],"<")==0)||(strcmp(tokens[i],">>")==0)){
            elements[j++] = i;
            elements[j++] = i+1;
        }
    }
    for(int i=0;i<j;i++)
    {
        pos = delete(tokens,elements[i],pos);
        //tokens[pos+1] = NULL;
    }
    free(elements);
    tokens[pos] = NULL; 
    return tokens;
}
void execute_with_pipes (char *input, int input_pipe) {
    int i, argc, append, pipefd[2];
    /* Check whether another pipe exists */
    char *next_command = strstr(input, "|");
    if (next_command != NULL) {
        *next_command = '\0';
        next_command++;
        if (pipe(pipefd) < 0) {
            perror("Pipe cannot be formed");
        }
    }

    char **argv = malloc(TOK_BUFF_SIZE);
    char *input_redir = NULL, *output_redir = NULL;
    argv = split_line (input);
    
    input_redir = input_file(argv);
    
    output_redir = output_file(argv);
    /* Check for append */
    append = isAppend(argv);
    argc = countToken(argv);
    
    /* Modify after removing all redirections */
    argv = modify_token(argv,argc); 
    
    int input_fd = -1, output_fd = -1;
    /* Check whether the input is sent through pipes or through redirection */
    if (input_pipe >= 0){
        input_fd = input_pipe;
    }
    else if (input_redir != NULL) 
    {
        input_fd = open(input_redir, O_RDONLY, 0);
    }
    if (next_command != NULL) {
        output_fd = pipefd[1];
    }
    /* Check whether the output is sent through pipes or through redirection */
    else if (output_redir != NULL) {
        if(!append)
            output_fd = open(output_redir, O_WRONLY|O_CREAT|O_TRUNC, 0644);
        else
            output_fd = open(output_redir, O_WRONLY|O_CREAT|O_APPEND, 0644);
    }
    execute (argv, input_fd, output_fd);
    free (argv);
    /* The pipe function is carried out recursively */
    if (next_command != NULL) {
        execute_with_pipes (next_command, pipefd[0]);
    }
}

