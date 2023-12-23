#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>


#define MAX_INPUT_BUFFER 100


bool readJobInputLine(){
    char buffer[MAX_INPUT_BUFFER];
    int cmd, param;
    if(fgets(buffer, MAX_INPUT_BUFFER, stdin) == NULL){//end of file
        printf("END OF STREAM\n");
        return false;
    }
    if(buffer[0] == '\n'){//only for my own input. 
        printf("EMPTY USER INPUT, END OF INPUT\n");
        return false;
    }
    //cmd
    if(buffer[0] == 'T'){
        printf("TRANS ");
        param = atoi(&buffer[1]);
        printf("%i\n", param);
    }
    else if(buffer[0] == 'S'){
        printf("SLEEP ");
        param = atoi(&buffer[1]);
        printf("%i\n", param);
    }
    else{
        printf("ERROR: Malformatted cmd");
        exit(1);
    }

    return true;
}


void main(){
    int t = (int)NULL;
    printf("val:%i\n",t);
}

