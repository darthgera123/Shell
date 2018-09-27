#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include "shellFunctions.h"
/* Checks for signals for Ctrl-c
	and prints it to stdout */
void exitHandler(int sig_num) {
    killy=1;
    fflush (stdout);
    return;
    
}
