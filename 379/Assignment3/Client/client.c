#include "client.h"

//steps
    //create socket
    //connect to server
    //set msg



void readIPFromArgs(int argc, char* argv[]){//read IP from args
    if(argc < 3){
        sprintf(g_connection_address, "127.0.0.1");//set to localhost on no IP args
        return;
    }
    strcpy(g_connection_address, argv[2]);
}


int sendWork(char* ipAddress, int port, char* command){//send work to server, return "D<n>" done value
    struct sockaddr_in address;
    int addressLen = sizeof(address);
    char writeBuffer[READ_BUFFER_SIZE] = {0};
    char readBuffer[READ_BUFFER_SIZE] = {0};
    //create socket
    int socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketFd == -1){
        printf("ERROR: could not create socket\n");
        exit(EXIT_FAILURE);
    }
    //printf("created socket\n");

    //setup address param
    address.sin_addr.s_addr = inet_addr(ipAddress);
    address.sin_family = AF_INET;
    address.sin_port = htons(port);//byte order stuff for port

    //connect to server
    if(connect(socketFd, (struct sockaddr*) &address, addressLen) < 0){
        printf("ERROR: could not connect\n");
        exit(EXIT_FAILURE);
    }
    int readReturn;//read in value to avoid compiler warning
    int returnVal;//D<n> value
    JobMessage returnJob;//container for decoded return value from server
    sprintf(writeBuffer, "%s %s.%i",command, g_hostname, g_pid);//format message for server
    //printf("client sending %s\n", writeBuffer);
    send(socketFd, writeBuffer, strlen(writeBuffer), 0);
    clientLogSend(getValueFromCommand(command));//update log with new transaction
    readReturn = recv(socketFd, readBuffer, READ_BUFFER_SIZE, 0);
    //printf("Client got msg: %s\n",readBuffer);
    close(socketFd);
    clientLogResv(getValueFromCommand(readBuffer));
    decodeJobCommand(readBuffer, &returnJob);
    return returnJob.value;
}

bool readJobInputLine(){//read one job from STDIN, returns false when all lines have been read, from assignment 2
    char buffer[MAX_INPUT_BUFFER];
    if(fgets(buffer, MAX_INPUT_BUFFER, stdin) == NULL){//end of file
        return false;
    }
    if(buffer[0] == '\n'){//only for my own input/testing. May remove later
        return false;
    }
    //check command/param
    if(buffer[0] == 'T'){
        char command[MAX_COMMAND_LENGTH];
        sprintf(command, "T%i",atoi(&buffer[1]));//remove newline with sprintf
        sendWork(g_connection_address, g_port, command);
    }
    else if(buffer[0] == 'S'){
        int param = atoi(&buffer[1]);
        clientLogSleep(param);
        Sleep(param);
    }
    else{
        printf("ERROR malformatted input command! \nnote: command is case sensitive\n");
        exit(1);
    }

    return true;
}

int main(int argc, char* argv[]){
    g_port = readPortFromArgs(argc, argv);
    readIPFromArgs(argc, argv);
    gethostname(g_hostname, MAX_HOST_NAME);
    g_pid =  getpid();
    initStats(g_pid, g_hostname, g_port);
    clientInit();
    while(readJobInputLine());//read input and send requests until finished
    clientLogTotalTransactions();
    return 0;
}