//functions needed for server log



void serverLogResv(int tid, int value, char* clientId){//log a T<n> job recieved from a client
    char outputBuffer[STRING_BUFFER_SIZE];
    sprintf(outputBuffer, "%.2lf: #%3d (T %i) from %s\n", getPartialTime(), tid + 1, value, clientId);
    writeToStatsFile(g_pid, g_hostname, outputBuffer);
}

void serverLogDone(int tid, char* clientId){//log the end of a T<n> job
    char outputBuffer[STRING_BUFFER_SIZE];
    sprintf(outputBuffer, "%.2lf: #%3d (Done) from %s\n", getPartialTime(), tid + 1, clientId);
    writeToStatsFile(g_pid, g_hostname, outputBuffer);
}

void serverLogExit(){//log exit stats
    char outputBuffer[STRING_BUFFER_SIZE*2];//could be long
    sprintf(outputBuffer, "SUMMARY\n");
    writeToStatsFile(g_pid, g_hostname, outputBuffer);
    for(int i = 0; i < g_clients_list.count; i++){
        sprintf(outputBuffer, "%4d transactions form %s\n", g_clients_list.clients[i]->count, g_clients_list.clients[i]->name);
        writeToStatsFile(g_pid, g_hostname, outputBuffer);
    }
    double totalTime = getPartialTime() - g_start_time - TIMER_PERIOD;//subtract TIMERPERIOD seconds because of timeout
    double tps = g_server_transaction_count / totalTime;
    
    sprintf(outputBuffer, "%4.1lf transactions/sec (%d/%.2lf)", tps, g_server_transaction_count, totalTime);
    writeToStatsFile(g_pid, g_hostname, outputBuffer);

}

