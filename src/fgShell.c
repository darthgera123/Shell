#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shellFunctions.h"

void fgShell(char **args) {
    
    if(args[1]==NULL){
        fprintf(stderr,"Please print out the job number");
        return;
    }
    int pid = getJobNum(atoi(args[1])), status, wpid;
    printf("%s %d",args[1],pid);
    if (pid < 0) {
        fprintf (stderr,"Job %s doesnot exist!\n", args[1]);
        return;
    }
    char *bgkill = new();
    strcpy(bgkill,bg_processes[pid]);
    free (bg_processes[pid]); bg_processes[pid] = NULL; 
    int killbg =0;
    for(int k=0;k<lastProcess;k++)
    {
        if(bg_order[k]==pid)
        {
            bg_order[k]=0;
            killbg=k;
            break;    
        }
    }
    while(waitpid(pid,&status,WNOHANG)!=pid)
            {
                if(killy == 1)
                {
                    kill(pid,9);
                    killy=0;
                    break;
                }
                if(bgy == 1)
                {
                    setpgid(pid,pid);
                    bg_order[killbg] = pid;
                    bg_processes[pid] = new();
                    strcpy(bg_processes[pid],bgkill);
                    kill(pid,SIGSTOP);
                    bgy=0;
                    break;
                }
            }
}

int bgShell(char **args){
    if(args[1]==NULL){
        fprintf(stderr,"Please print the job number");
        return 1;
    }
    int jobPid = getJobNum(atoi(args[1]));
    if(jobPid < 0){
        fprintf (stderr,"Job %s doesnot exist!\n", args[1]);
        return 1;
    }
    if(kill(jobPid,SIGCONT)<0){
        fprintf(stderr,"Job %s doesnt exist! \n",args[1]);
        return 1;
    }
}