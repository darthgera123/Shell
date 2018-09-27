#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "shellFunctions.h"

/* Function to conver inter to string */
void tostring(char *str, int num)
{
    int i, rem, len = 0, n;
    n = num;
    while (n != 0)
    {
       len++;
        n /= 10;
    }
   for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

int pinfoShell(char **args)
{
    /* The pid is converted into a string */
    char *process = new();
    if(args[1]!=NULL&&strcmp(args[1],"&")!=0)
    {
        process = args[1];
    }
    else
    {
        tostring(process,getpid());
    }
    /* /proc/<pid>/status has valuable information */
    char pathStatus[buffer_size] = "/proc/";
    strcat(pathStatus,process);
    strcat(pathStatus,"/status");
    /* Opening and reading the file line by line */
    FILE * status;
    char *line =NULL;
    size_t len = 0;
    ssize_t read;
    status = fopen(pathStatus,"r");
    /* If the process exists then the file will also be present */
    if(status == NULL)
    {
        fprintf(stderr,"No such process\n");
        return 1;
    }
    printf("PID : %s\n",process);
    /* Reading the file line by line and tokenizing to get information */
    while((read = getline(&line,&len,status))!= -1)
    {
        char **args = split_line(line);
        if(strcmp(args[0],"State:")==0)
            printf("Process Status : %s\n",args[1]);
        if(strcmp(args[0],"VmSize:")==0)
            printf("Memory: %s\n",args[1]);
    }
    fclose(status);
    if(line)
        free(line);
    /* Reading the link to which it points */
    char exeStatus[buffer_size] = "/proc/";
    strcat(exeStatus,process);
    strcat(exeStatus,"/exe");
    char *exePath = new();
    read = readlink(exeStatus,exePath,buffer_size-1);
    if(!read)
    {
        fprintf(stderr,"Link does not exist\n");
        return 1;
    }
    /* Manipulating the path */
    char *finalPath = new();
    int istilda = 1;
    int home_length = strlen(home);
    int exe_length = strlen(exePath);
    if(exe_length<home_length)
    {
        finalPath = exePath;
    }
    else{
        for(int i=0;home[i]!='\0';i++)
        {
            if(exePath[i]!=home[i]){
                istilda = 0;
                break;
            }
        }
    }
    if(istilda)
    {
        finalPath[0]='~';
        finalPath[1]='/';
        int j=2;
        for(int i=home_length+1;exePath[i]!='\0';i++)
        {
            finalPath[j++] = exePath[i]; 
        }
        finalPath[j]='\0';
        
    }
    else{
        finalPath = exePath;
    }
    
    printf("Executable: %s\n",finalPath);
    free(finalPath);
    free(exePath);
    return 1;
}