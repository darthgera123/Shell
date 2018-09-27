#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "shellFunctions.h"


void bgChecker(int sig_num) {
    //printf("%d",pid);
        pid_t pid;
        int status;
        pid= waitpid(-1, &status, WNOHANG);
        if (bg_processes[pid])
        {
        printf("[%d] - %s process has been ", pid,bg_processes[pid]);
        if(WIFEXITED(status))
        printf("normally killed\n");
        else{
            printf("with exit status %d\n", WEXITSTATUS(status));
        }
        free(bg_processes[pid]);
        bg_processes[pid] = NULL;
        fflush (stdout);
        } 
}
