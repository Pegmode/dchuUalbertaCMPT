//functions needed for client log

void clientInit(){//append client specific log information
    char outputBuffer[STRING_BUFFER_SIZE];
    sprintf(outputBuffer, "Using server address %s\nHost %s.%i\n", g_connection_address, g_hostname, g_pid);
    writeToStatsFile(g_pid, g_hostname, outputBuffer);
}

void clientLogSend(int value){//log a T<n> job sent to server
    char outputBuffer[STRING_BUFFER_SIZE];
    sprintf(outputBuffer, "%.2lf: Send (T %i)\n", getPartialTime(), value);
    writeToStatsFile(g_pid, g_hostname, outputBuffer);
}

void clientLogResv(int value){//log a D<n> job recieved from server
    char outputBuffer[STRING_BUFFER_SIZE];
    sprintf(outputBuffer, "%.2lf: Recv (D %i)\n", getPartialTime(), value);
    writeToStatsFile(g_pid, g_hostname, outputBuffer);
    g_transaction_count++;
}

void clientLogSleep(int value){//log a S<n> input that client read
    char outputBuffer[STRING_BUFFER_SIZE];
    sprintf(outputBuffer, "Sleep %i units\n", value);
    writeToStatsFile(g_pid, g_hostname, outputBuffer);
}

void clientLogTotalTransactions(){//log total transactions 
    char outputBuffer[STRING_BUFFER_SIZE];
    sprintf(outputBuffer, "Sent %i transactions\n", g_transaction_count);
    writeToStatsFile(g_pid, g_hostname, outputBuffer);
}
