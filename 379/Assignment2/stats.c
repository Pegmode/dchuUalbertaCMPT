//functions to generate logs
#define MAX_LOG_LINESIZE 300


// END STATS
//====================================================================================

EndStats* endStatsInit(int numThreads){///setup stats tracking for end of program
	EndStats* endStats = (EndStats*) malloc(sizeof(EndStats));
	endStats->work = 0;
	endStats->ask = 0;
	endStats->receive = 0;
	endStats->sleep = 0;
	endStats->complete = 0;
    //threads
    endStats->threadSize = numThreads;
    endStats->threads = (int*) malloc(sizeof(int)*numThreads);
    return endStats;
}

void incEndStat(int* stat){//increment one of the end stats safely
    pthread_mutex_lock(&g_endStats->mutexLock);
    (*stat)++;
    pthread_mutex_unlock(&g_endStats->mutexLock);
}

void incEndThreadStat(int threadId){//increment one of the end thread stats safely
    //note that threadID is the iter value + 1 that is used in consumer
    int* stat = &g_endStats->threads[threadId-1];
    pthread_mutex_lock(&g_endStats->mutexLock);
    (*stat)++;
    pthread_mutex_unlock(&g_endStats->mutexLock);
}

void writeEndStatLine(char* name, int count ,FILE* f){//write a single line to file for the end stats
    char writeBuffer[MAX_LOG_LINESIZE]; 
    sprintf(writeBuffer, "  %-12s   %4i\n", name, count);
    fwrite(writeBuffer, strlen(writeBuffer), 1, f);
}

void writeEndThreadStatLine(int thread, int count, FILE* f){//write a single line for the thread portion of the end statss
    char writeBuffer[MAX_LOG_LINESIZE]; 
    sprintf(writeBuffer, "  Thread%3i       %3i\n", thread, count);
    fwrite(writeBuffer, strlen(writeBuffer), 1, f);
}

void generateEndStats(){//Write the final stats when all threads are finished
//ONLY CALL WHEN ALL THREADS HAVE COMPLETED
    FILE* f;
    f = fopen(g_logFilename, "a");
    if(f == NULL){
        printf("Error Opening file %s\n", g_logFilename);
        exit(1);
    }
    char* summaryString = "Summary:\n";
    fwrite(summaryString, strlen(summaryString), 1, f);
    writeEndStatLine("Work", g_endStats->work, f);
    writeEndStatLine("Ask", g_endStats->ask, f);
    writeEndStatLine("Receive", g_endStats->receive, f);
    writeEndStatLine("Complete", g_endStats->complete, f);
    writeEndStatLine("Sleep", g_endStats->sleep, f);
    for(int i = 0; i < g_endStats->threadSize; i++){
        int threadID = i+1;
        int count = g_endStats->threads[i];
        writeEndThreadStatLine( threadID, count, f);
    }
    int work = g_endStats->work;
    float totalTime= elapsedTime();
    float transPerSec = work / totalTime;
    char writeBuffer[MAX_LOG_LINESIZE];
    sprintf(writeBuffer, "Transactions per second:%3.2f\n", transPerSec);
    fwrite(writeBuffer, strlen(writeBuffer), 1, f);

    fclose(f);

}


// GENERAL EVENTS STATS
//====================================================================================

void writeLogEntry(double time, int id, int q, char* type, int n){
    char writeBuffer[MAX_LOG_LINESIZE];
    if(strcmp(type, "Ask") == 0 || strcmp(type, "End") == 0 ){//Ask 
        sprintf(writeBuffer, "  %-4.3lf  ID= %-3i        %-15s\n",time ,id, type);
    }
    else if(strcmp(type, "Sleep") == 0){//Sleep
        sprintf(writeBuffer, "  %-4.3lf  ID= %-3i        %-15s %-3i\n",time ,id, type, n);
    }
    else{//others
        sprintf(writeBuffer, "  %-4.3lf  ID= %-3i Q= %-3i %-15s %-3i\n",time ,id, q, type, n);
    }

    pthread_mutex_lock(&g_fileLock);
    //write
    FILE* f;
    f = fopen(g_logFilename, "a");
    if(f == NULL){
        printf("Error Opening file %s\n", g_logFilename);
        exit(1);
    }
    fwrite(writeBuffer, strlen(writeBuffer), 1, f);
    fclose(f);
    pthread_mutex_unlock(&g_fileLock);

}

//Functions to write Events to log
void logAsk(int id){
    double time = elapsedTime();
    writeLogEntry(time, id, -1, "Ask", -1);
    incEndStat(&g_endStats->ask);

}

void logReceive(int id, int q, int n){
    double time = elapsedTime();
    writeLogEntry(time, id, q, "Receive", n);
    incEndStat(&g_endStats->receive);
}

void logWork(int id, int q, int n){
    double time = elapsedTime();
    writeLogEntry(time, id, q, "Work", n);
    incEndStat(&g_endStats->work);

}

void logComplete(int id, int q, int n){
    double time = elapsedTime();
    writeLogEntry(time, id, q, "Complete", n);
    incEndStat(&g_endStats->complete);
}

void logEnd(int id){
    double time = elapsedTime();
    writeLogEntry(time, id, -1, "End", -1);
}

void logSleep(int id, int n){
    double time = elapsedTime();
    writeLogEntry(time, id, -1, "Sleep", n);
    incEndStat(&g_endStats->sleep);
}

