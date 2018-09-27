#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include "shellFunctions.h"
int jobsShell (char **args) {
    int i, j = 1;
    for (i = 0; i < 32768; i++) {
        if (bg_processes[bg_order[i]]){
            char path[buffer_size] = "/proc/";
            char *pidNo =new();
            tostring(pidNo,bg_order[i]);
            strcat(path,pidNo);
            strcat(path,"/status");
            FILE * status;
                char *line =NULL;
                size_t len = 0;
                ssize_t read;
                status = fopen(path,"r");
             while((read = getline(&line,&len,status))!= -1)
                {
                    char **args = split_line(line);
                    if(strcmp(args[0],"State:")==0){
                        if(strcmp(args[1],"T")==0)
                            printf("[%d] Stopped %s[%d]\n",j++,bg_processes[bg_order[i]], bg_order[i]);
                        else 
                            printf("[%d] Running %s[%d]\n",j++,bg_processes[bg_order[i]], bg_order[i]);
                        
                        break;
                    }
                }
            fclose(status);
        }
    }
}


int kjobsShell(char **args)
{
    if(args[1]==NULL || args[2]==NULL)
    {
        fprintf(stderr,"Format is kjobs <job num> <signal num>\n");
        return 1;
    }
    int jpid = getJobNum(atoi(args[1]));
    //printf("%d",jpid);
    int signal = atoi(args[2]);
    if(jpid == -1){
        fprintf(stderr,"Jobs doesnt exist\n");
    }
    kill(jpid,signal); 
    return 1;
    
}