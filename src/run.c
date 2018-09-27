#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "shellFunctions.h"

char *built[] = {"exit","cd","pwd","echo","ls","pinfo","clock","overkill","kjobs","setenv","unsetenv","fg","getenv","jobs","bg"};
commands builtin[] = {&exitShell,&cdShell,&pwdShell,&echoShell,&lsShell,&pinfoShell,&clockShell,&overkillShell,&kjobsShell,&setenvShell,&unsetenvShell,&fgShell,&getenvShell,&jobsShell,&bgShell};


void sighandler(int sig_num) 
{ 
    // Reset handler to catch SIGTSTP next time 
    bgy=1;
    return;
} 
int launch(char **args,int input_fd,int output_fd)
{
    //Fork has to be created to run every new process. If pid =0, we exec the new process
    //If its a background process then we dont wait for the pid else we wait for the pid to finish

    int bg =0;
    for(int i=0;args[i]!=NULL;i++)
    {
        if(strcmp(args[i],"&")==0)
        {
            bg=1;
            args[i]= NULL;
        }
    }
    pid_t pid;
    int status;
    pid = fork();
    if(pid == 0)
    {
        if (input_fd >= 0) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }
        if (output_fd >= 0) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }
        //child process will run
        long int count = sizeof(builtin)/sizeof(int*);
        for(long int i=0;i<count;i++)
        {
        if(strcmp(args[0],built[i])==0)
        {
            builtin[i](args);
            exit(EXIT_SUCCESS);
        }
    }
        if(execvp(args[0],args)==-1)
            perror("shell");
        exit(EXIT_FAILURE);
    }
    else if(pid<0)
    {
        perror("shell");
    }
    if(pid>0){
        if (input_fd >= 0) close (input_fd);
        if (output_fd >= 0) close (output_fd);
        if (!bg){
            //parent process runs when on foreground
            signal(SIGINT,exitHandler);
            signal(SIGTSTP, sighandler); 
            do{ 
                waitpid(pid,&status, WUNTRACED);
                if(killy == 1)
                {
                    kill(pid,9);
                    killy=0;
                    break;
                }
                if(bgy == 1)
                {
                    if(strcmp(args[0],"fg")==0)
                        break;
                    setpgid(pid,pid);
                    bg_order[lastProcess++] = pid;
                    bg_processes[pid] = new();
                    strcpy(bg_processes[pid],args[0]);
                    kill(pid,SIGSTOP);
                    bgy=0;
                    break;
                }
                // WUNTRACED proceeds when child returns
            }while(!WIFEXITED(status)&& !WIFSIGNALED(status));
            //WIFEXITED = if child returns normally
            //WIFSIGNALED = if child returns throuh some signal
        }
        else {
            bg_order[lastProcess++] = pid;
            bg_processes[pid] = new();
            strcpy(bg_processes[pid],args[0]);
        }
    }
    return 1;
}

int execute(char **args,int input_fd,int output_fd)
{
    if(args[0]==NULL)
        return 1;
    //checking number of user defined process 
    
    if(strcmp(args[0],"quit")==0)
        exit(EXIT_SUCCESS);
    return launch(args,input_fd,output_fd);    
}