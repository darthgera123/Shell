//Standard library declarations
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include "shellFunctions.h"

int main()
{
    //signal(SIGTSTP,SIG_IGN);
    signal(SIGINT, SIG_IGN);
    lastProcess = 0;
    killy=0;
    bgy=0;
    home =  new();
    getcwd(home,buffer_size);
    shell_loop();
    free(home);
    return 0;
}