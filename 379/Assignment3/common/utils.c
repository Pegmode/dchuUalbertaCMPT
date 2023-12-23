//utility functions common to server and client

int readPortFromArgs(int argc, char* argv[]){//read program args
    if(argc < 2){
        printf("ERROR: must give port number as first arguement!\n");
        exit(0);
    }
    int port = atoi(argv[1]);
    if ((port > PORT_HIGH_LIMIT)||(port <PORT_LOW_LIMIT)){
        printf("ERROR: port number is outside of allowed range (%i-%i)\n", PORT_LOW_LIMIT, PORT_HIGH_LIMIT);
        exit(0);
    }
    return port;
}


void decodeJobCommand(char* command, JobMessage* job){//decode job command and put into JobMessage
    job->type = command[0];
    job->value = atoi(&command[1]);
}

void encodeJobCommand(char* command, JobMessage* job){//decode job command and put into JobMessage
    command[0] = job->type;
    sprintf(&command[1], "%i", job->value);
}

int getValueFromCommand(char* command){
    return atoi(&command[1]);
}