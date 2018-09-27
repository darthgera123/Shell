#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "shellFunctions.h"

int clockShell(char **args)
{
    char *clock = new();
    /* error checking */
    if(args[1]==NULL||args[2]==NULL||args[1][0]!='-'||args[1][1]!='t')
    {    
        fprintf(stderr,"Arguments must be -t <time>\n");
        return 1;
    }
    /* /proc/driver/rtc has valuable information */
    char pathStatus[buffer_size] = "/proc/driver/rtc";
    /* Opening and reading the file line by line */
    
    /* Reading the file line by line and tokenizing to get information */
    while(1)
        {
        char *line =NULL;
        size_t len = 0;
        ssize_t read;
        FILE * status;
        status = fopen(pathStatus,"r");
        /* If the process exists then the file will also be present */
        if(status == NULL)
        {
            fprintf(stderr,"No such file\n");
            return 1;
        }

        while((read = getline(&line,&len,status))!= -1)
        {
            char **args = split_line(line);
            if(strcmp(args[0],"rtc_date")==0)
                printf("Date : %s\n",args[2]);
            if(strcmp(args[0],"rtc_time")==0)
                printf("Time: %s\n",args[2]);
        }
        free(args);
        
        if(line)
            free(line);
        fclose(status);
        
        sleep(atoi(args[2]));
    }
    
    
    return 1;
}