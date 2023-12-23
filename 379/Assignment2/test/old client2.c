#include "client.h"

//steps
    //create socket
    //connect to server
    //set msg

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
    printf("created socket\n");

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
    send(socketFd, command, strlen(command), 0);

    //readReturn = read(socketFd, readBuffer, READ_BUFFER_SIZE);
    readReturn = recv(socketFd, readBuffer, READ_BUFFER_SIZE, 0);

    printf("Client got msg: %s\n",readBuffer);
    close(socketFd);
    decodeJobCommand(readBuffer, &returnJob);
    return returnJob.value;
}

int main(int argc, char* argv[]){
    JobMessage job;
    job.type = 'T';
    job.value = 69;
    gethostname(G_HOSTNAME, MAX_HOST_NAME);
    G_PID =  getpid();
    sendWork("127.0.0.1", T_PORT, "T20");
    return 0;

}