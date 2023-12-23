#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>


int main( void ) {
	FILE * pfile;
	int c;
    int pid = 14335;//temp

    char out[50];
    char inS[50];
    sprintf(out,"ps -ho cputime -p %d",pid);
    //printf("FORMATTED:%s\n",out);

	// Open the pipe. The pipe's output (i.e., the results of the "sort" command
	// will be available for reading by this program (accessible as FILE "pfile")
	if( ( pfile = popen( out, "r" ) ) == NULL ) {
		perror( "Pipe open failure\n" );
	} else {
		//printf( "START: print lines of text in pipe.c sorted\n" );

		// Read the the pipe until end-of-file is reached.
        fscanf(pfile, "%s", inS);

        int t;// atoi(currentRequestStr.args[1]);
        int stringSize = strlen(inS);
        printf("STRING SIZE: %d\n",stringSize);
        inS[stringSize - 3] = '\0';//add null term
        t = atoi(&inS[3]);


        printf("%d\n",t);

		if( pclose( pfile ) ) {
			perror( "Pipe close failure\n" );
		}
	}
	return( 0 );
}

/*
current best ps pipe:
ps -ho cputime -p [PID]
*/


