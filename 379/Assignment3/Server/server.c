#include "server.h"

//steps
    //create socket
    //bind socket struct options to socket
    //listen
    //accept


void shutdownServer(){
    serverLogExit();
    exit(0);
}

int main(int argc, char* argv[]){
    //
    //init
    //
    g_start_time =  getPartialTime();
    initClientsList();
    gethostname(g_hostname, MAX_HOST_NAME);
    g_pid =  getpid();
    int port = readPortFromArgs(argc, argv);
    initStats(g_pid, g_hostname, port);
    //init socket
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int socketFd = socket(AF_INET, SOCK_STREAM, 0);
    char connectionBuffer[READ_BUFFER_SIZE] = {0};
    //create socket
    if(socketFd == -1){
        printf("ERROR: could not create socket\n");
        exit(EXIT_FAILURE);
    }
    struct timeval timeOut;
    timeOut.tv_sec = TIMER_PERIOD;//timeout
    timeOut.tv_usec = 0;
    setsockopt(socketFd, SOL_SOCKET, SO_RCVTIMEO, &timeOut, sizeof timeOut);
    //setup address properties
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);//byte order for port
    //bind socket to address
    if (bind(socketFd, (struct sockaddr*) &address, sizeof(address)) < 0){
        printf("ERROR: could not bind socket\n");
        exit(EXIT_FAILURE);
    }
    //set socket to listen
    if (listen(socketFd, MAX_BACKLOG) < 0){
        printf("ERROR: could not listen to socket\n");
        exit(EXIT_FAILURE);
    }  
    int connectionFd, readReturn;


    //
    //MAIN LOOP
    //

    while(true){
    JobMessage job;//used for message decoding
    //accept new connection in queue

    if ((connectionFd = accept(socketFd, (struct sockaddr*) &address, (socklen_t*) &addrlen)) < 0){
        //TIMEOUT!
        shutdownServer();

    }
    readReturn = recv(connectionFd, connectionBuffer, READ_BUFFER_SIZE, 0);

    char command[50] = {0};
    char clientID[50] = {0};

    sscanf(connectionBuffer, "%s %s", command, clientID);
    decodeJobCommand(command, &job);//decode command into job 

    if(job.type == 'T'){//if message is correct type do work
        //resetTimer();
        //printf("MSG:%s from: %s\n", command, clientID);
        serverLogResv(g_server_transaction_count, job.value, clientID);
        Trans(job.value);//do work 
        serverLogDone(g_server_transaction_count, clientID);
        g_server_transaction_count++;
        incClientCount(clientID);
    }
    else{
        printf("WARNING: Server received non transaction command, ignoring command..\n");
    }

    char rtnMsg[50];
    sprintf(rtnMsg, "D%i", g_server_transaction_count);//send done message to client
    send(connectionFd, rtnMsg, strlen(rtnMsg), 0);
    close(connectionFd);    
    }

}