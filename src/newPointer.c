#include <stdlib.h>
#include "shellFunctions.h"

/* Function to create a new pointer */
char *new()
{
    char *newp = (char*)malloc(buffer_size*sizeof(char));
    return newp;
}