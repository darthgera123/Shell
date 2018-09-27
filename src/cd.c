#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shellFunctions.h"

//Used for switching directories
int cdShell(char **args)
{
    if(args[1]==NULL)
    {
        fprintf(stderr, "shell:expected argument to be \"cd\"<filename> \n");
    }
    else{
        if(chdir(args[1]))
        {
            perror("shell");
        }
    }
    return 1;
}