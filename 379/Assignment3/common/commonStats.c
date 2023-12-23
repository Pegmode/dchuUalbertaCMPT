//stats functions common to both client and server

void initStats(int PID, char* hostName, int port){//initialize log and add port number 
    char logFileName[STRING_BUFFER_SIZE];
    char outputBuffer[STRING_BUFFER_SIZE];
    sprintf(logFileName, "%s.%i", hostName, PID);//format filename
    sprintf(outputBuffer, "Using port %i\n", port);
	FILE* f;
    f = fopen(logFileName, "w");
    if(f == NULL){
        printf("Error Opening file %s\n", logFileName);
        exit(1);
    }
    fwrite(outputBuffer, strlen(outputBuffer), 1, f);
    fclose(f);
}

void writeToStatsFile(int PID, char* hostName, char* outputBuffer){//opens stats file and writes a string to it
    char logFileName[STRING_BUFFER_SIZE];
    sprintf(logFileName, "%s.%i", hostName, PID);//format filename
	FILE* f;
    f = fopen(logFileName, "a");
    fwrite(outputBuffer, strlen(outputBuffer), 1, f);
    fclose(f);
}

double getPartialTime(){//get epoch time with partial seconds
    clockid_t clk_id;
    struct timespec currentTime;
    clock_gettime(CLOCK_REALTIME, &currentTime);
    //printf("RAW:%lld.%2.ld\n\n", (long long)currentTime.tv_sec, currentTime.tv_nsec);
    return (double)currentTime.tv_sec+(double)(currentTime.tv_nsec / 1000000000.0);
}


