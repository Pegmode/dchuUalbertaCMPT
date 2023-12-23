#include <stdio.h>
#include <stdlib.h>

void buildLogString(int id, char* outString){//parse args to build filename for log
    if(id != -1){
        sprintf(outString, "prodcon.%i.log", id);
    }
    else{//could keep argv string but I don't wana deal with malloc
        sprintf(outString, "prodcon.log");
    }
}


void parseProgArgs(int argc, char** argv, int* consumerCount, int* id){//parse args given to prodcon when called
	if(argc == 1){
		printf("Error: no arguements given\n");
		exit(1);
	}
	else if(argc == 2){
		*consumerCount = atoi(argv[1]);
		*id = -1;
	}
	else{//id given, need to also account for input redirection
		*consumerCount = atoi(argv[1]);
		*id = atoi(argv[2]);
	}
}

float elapsedTime(){//calculate how much time hahs passed since g_baseClock
	clock_t currentClock = clock();
	double currentTime = (double)(currentClock - g_baseClock) / CLOCKS_PER_SEC ;
	return currentTime;
}

void clearLogFile(){//clear log file on init
	    FILE* f;
    f = fopen(g_logFilename, "w");
    if(f == NULL){
        printf("Error Opening file %s\n", g_logFilename);
        exit(1);
    }
    fclose(f);
}