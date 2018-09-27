#include <sys/utsname.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "shellFunctions.h"


/* Main shell loop */
void shell_loop()
{
    char *line;
    char **commands;
    int status=1;
    signal(SIGCHLD, bgChecker);
    while(1) {
        prompt();
        char *line;
        line = read_line();
        commands = split_command(line);
        for(int i=0;commands[i]!=NULL;i++){
            execute_with_pipes(line,-1);
        }
    }
    free(line);
    free(commands);
}
