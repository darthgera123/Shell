#include <stdlib.h>
#include <stdio.h>
#include "shellFunctions.h"

int setenvShell(char **args) {
	if (args[2] == NULL) {
        args[2] = " ";
    }
	if (setenv(args[1],args[2],1) != 0) 
    {
        perror("shell");
    }
	return 1;	
}

int unsetenvShell (char **args) {
	if (unsetenv(args[1]) != 0) perror("shell");
	return 1;
}

int getenvShell (char **args) {
    if(getenv(args[1])==0)
    {
        fprintf(stderr,"Please check the format\n");
    }
    else{
        printf("%s\n",getenv(args[1]));
    }
}