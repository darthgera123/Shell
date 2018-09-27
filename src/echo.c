#include <stdio.h>
#include "shellFunctions.h"

/* Function for user defined echo */
int echoShell(char **args)
{
    for(int i=1;args[i]!=NULL;i++)
    {
        printf("%s ",args[i]);
    } 
    printf("\n");
    return 1;
}