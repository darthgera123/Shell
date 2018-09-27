#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include "shellFunctions.h"

int pwdShell(char **args)
{
    char *path = new();
    getcwd(path,1024);
    printf("%s\n",path);
    free(path);
    return 1;
}
