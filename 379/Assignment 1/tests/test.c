#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>


int main( void ) {
    char test[100];
    scanf("%s",test);
    printf("ECHO: %s\n",test);
	return( 0 );
}

/*
current best ps pipe:
ps -ho cputime -p [PID]
*/


