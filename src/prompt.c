#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "shellFunctions.h"

/* This function checks for home */
char *finalPath()
{
    char *path = new();
    getcwd(path,1024);
    int path_length = strlen(path);
    int home_length = strlen(home);
    if(path_length < home_length)
        return path;
    else 
    {
        char *finalpath = new();
        int j = 2;
        finalpath[0]='~';
        finalpath[1]='/';
        for(int i=home_length+1;path[i]!='\0';i++)
        {
            finalpath[j++] = path[i]; 
        }
        free(path);
        finalpath[j]='\0';
        return finalpath;
    }
}
int prompt()
{
    uid_t uid;
    struct passwd *pw;
    uid = geteuid();
    pw = getpwuid(uid);
    char *sysname,*name,*path;
    sysname = new();
    name = new();
    name = pw->pw_name;
    int err = gethostname(sysname,1000);
    if(err<0)
    {
        return 0;
    }
    path=finalPath();
    printf("<%s@%s:%s>",name,sysname,path);
    free(name);
    free(sysname);
    free(path);
    return 1;
}