#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include "shellFunctions.h"

/* User defined ls implemented. Prints permissions,owners, last modification time */
int lsShell(char **args)
{
    int full =0;
    int hidden =0;
    char *path = new();
    path = ".";
    for(int i=1;args[i]!=NULL;i++)
    {
        if(args[i][0]=='-')
        {
            if(args[i][1] == 'a')
                hidden =1;
            if(args[i][1] == 'l')
                full = 1;
            if(args[i][2]!='\0'&&args[i][2] == 'a')
                hidden =1;
            if(args[i][2]!='\0'&&args[i][2] == 'l')
                full =1;
        }
        else{
            path = args[i];
        }
        
    } 
    struct stat check;
    struct dirent *dir;
    char *name = path;
    DIR *tempdir = opendir(path);
    //Check if its a file or directory
    if(tempdir == NULL)
    {
        
        int isFile = stat(path,&check);
        
        if(isFile==0)
        {
            
            if(full == 1){
            int fileMode = check.st_mode;
            char permission[11] = {'-','-','-','-','-','-','-','-','-','-'};
            if ((fileMode & S_IRUSR) && (fileMode & S_IREAD))
            {
                permission[1] = 'r';
            }
            if ((fileMode & S_IWUSR) && (fileMode & S_IWRITE))
            {
                permission[2] = 'w';
            }
            if ((fileMode & S_IXUSR) && (fileMode & S_IEXEC))
            {   
                permission[3] = 'x';
            }
            if ((fileMode & S_IRGRP) && (fileMode & S_IREAD))
            {
                permission[4] = 'r';
            }
            if ((fileMode & S_IWGRP) && (fileMode & S_IWRITE))
            {
                permission[5] = 'w';
            }
            if ((fileMode & S_IXGRP) && (fileMode & S_IEXEC))
            {
                permission[6] = 'x';
            }
            if ((fileMode & S_IROTH) && (fileMode & S_IREAD))
            {
                permission[7] = 'r';
            }
            if ((fileMode & S_IWOTH) && (fileMode & S_IWRITE))
            {
                permission[8] = 'w';
            }
            if ((fileMode & S_IXOTH) && (fileMode & S_IEXEC))
            {
                permission[9] = 'x';
            }
            char *token = strtok(ctime(&check.st_mtime),TOK_DELIM);
            char **tokens = malloc(buffer_size*sizeof(char*));
            int pos=0;
            while(token!=NULL)
            {
                tokens[pos++]=token;
                token = strtok(NULL," ");
            }
            struct passwd *pw = getpwuid(check.st_uid);
            struct group  *gr = getgrgid(check.st_gid);
            printf("%s\t%ld\t%s\t%s\t%s %s\t%s ",permission,check.st_size,pw->pw_name,gr->gr_name,tokens[1],tokens[2],tokens[3]);
            
            }
            printf("%s\n",name);
            return 1;

        }     
        fprintf(stderr,"Could not open current directory\n");
        return 1;
    }
    while((dir = readdir(tempdir)) != NULL)
    {
        if(!full){
            if(hidden)
                printf("%s\t",dir->d_name);
            else
            {
                if(dir->d_name[0] != '.')
                    printf("%s\t",dir->d_name);
            }
        }
        else{
            struct stat attrib;
            char *fname = dir->d_name;
            stat(fname,&attrib);
            int fileMode = attrib.st_mode;
            char permission[11] = {'-','-','-','-','-','-','-','-','-','-'};
            if(S_ISDIR(fileMode))
            {
                permission[0]='d';
            }
            
            if ((fileMode & S_IRUSR) && (fileMode & S_IREAD))
            {
                permission[1] = 'r';
            }
            if ((fileMode & S_IWUSR) && (fileMode & S_IWRITE))
            {
                permission[2] = 'w';
            }
            if ((fileMode & S_IXUSR) && (fileMode & S_IEXEC))
            {   
                permission[3] = 'x';
            }
            if ((fileMode & S_IRGRP) && (fileMode & S_IREAD))
            {
                permission[4] = 'r';
            }
            if ((fileMode & S_IWGRP) && (fileMode & S_IWRITE))
            {
                permission[5] = 'w';
            }
            if ((fileMode & S_IXGRP) && (fileMode & S_IEXEC))
            {
                permission[6] = 'x';
            }
            if ((fileMode & S_IROTH) && (fileMode & S_IREAD))
            {
                permission[7] = 'r';
            }
            if ((fileMode & S_IWOTH) && (fileMode & S_IWRITE))
            {
                permission[8] = 'w';
            }
            if ((fileMode & S_IXOTH) && (fileMode & S_IEXEC))
            {
                permission[9] = 'x';
            }
            char *token = strtok(ctime(&attrib.st_mtime),TOK_DELIM);
            char **tokens = malloc(buffer_size*sizeof(char*));
            int pos=0;
            while(token!=NULL)
            {
                tokens[pos++]=token;
                token = strtok(NULL," ");
            }
            struct passwd *pw = getpwuid(attrib.st_uid);
            struct group  *gr = getgrgid(attrib.st_gid);
            if(hidden)
                
                printf("%s\t%ld\t%s\t%s\t%s %s\t%s %s\n",permission,attrib.st_size,pw->pw_name,gr->gr_name,tokens[1],tokens[2],tokens[3],dir->d_name);
                
            else{
                if(dir->d_name[0] !='.')
                   printf("%s\t%ld\t%s\t%s\t%s %s\t%s %s\n",permission,attrib.st_size,pw->pw_name,gr->gr_name,tokens[1],tokens[2],tokens[3],dir->d_name); 
            }
        }
        
    }
    printf("\n");
    closedir(tempdir);
    free(dir);
    return 1;
}