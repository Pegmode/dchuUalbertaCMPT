#include "client.h"

//steps
//create socket
//bind socket struct options to socket



int main(int argc, char* argv[]){
    struct sockaddr_in address;
    int addressLen = sizeof(address);
    char* msg = "Hello loser!";
    //create socket
    int socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketFd == -1){
        printf("ERROR: could not create socket\n");
        exit(EXIT_FAILURE);
    }
    printf("created socket\n");

    //bind socket
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_family = AF_INET;
    address.sin_port = htons(T_PORT);//byte order stuff for port

    if(connect(socketFd, (struct sockaddr*) &address, sizeof(address)) < 0){
        printf("ERROR: could not connect\n");
        exit(EXIT_FAILURE);
    }

    send(socketFd, msg, strlen(msg), 0);
    printf("sent msg!\n");
    close(socketFd);
    return 0;

}