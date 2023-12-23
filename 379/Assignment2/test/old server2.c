#include "server.h"

//steps
    //create socket
    //bind socket struct options to socket
    //listen
    //accept




int main(int argc, char* argv[]){



    int port = readPortFromArgs(argc, argv);

    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char* msg = "This is a test!";
    int socketFd = socket(AF_INET, SOCK_STREAM, 0);
    char connectionBuffer[READ_BUFFER_SIZE] = {0};
    if(socketFd == -1){
        printf("ERROR: could not create socket\n");
        exit(EXIT_FAILURE);
    }

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);//byte order for port

    if (bind(socketFd, (struct sockaddr*) &address, sizeof(address)) < 0){
        printf("ERROR: could not bind socket\n");
        exit(EXIT_FAILURE);
    }

    if (listen(socketFd, MAX_BACKLOG) < 0){
        printf("ERROR: could not listen to socket\n");
        exit(EXIT_FAILURE);
    }  

    int connectionFd, readReturn;
    while(true){
    JobMessage job;
    if ((connectionFd = accept(socketFd, (struct sockaddr*) &address, (socklen_t*) &addrlen)) < 0){
        printf("ERROR: could not accept socket connection\n");
        exit(EXIT_FAILURE);
    }
    //readReturn = read(connectionFd, connectionBuffer, READ_BUFFER_SIZE);
    readReturn = recv(connectionFd, connectionBuffer, READ_BUFFER_SIZE, 0);
    decodeJobCommand(connectionBuffer, &job);



    printf("MSG:%c%i\n", job.type, job.value);
    char* rtnMsg = "D420";

    send(connectionFd, rtnMsg, strlen(rtnMsg), 0);
    close(connectionFd);    
    }

}