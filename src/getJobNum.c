#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "shellFunctions.h"

int getJobNum(int jobPid){
    int i,j=0;
    for( i=0;i<32767;i++)
    {
        if(j==jobPid){
            break;
        }
        if(bg_processes[bg_order[i]])
            j++;
    }
    if(i==32767)
    return -1;
    return bg_order[i-1];
}