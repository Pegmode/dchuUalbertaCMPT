//common headder file to server and client

//constants
#define PORT_LOW_LIMIT 5000
#define PORT_HIGH_LIMIT 64000
#define T_PORT 5001//test port
#define MAX_BACKLOG 5
#define READ_BUFFER_SIZE 1024
#define STRING_BUFFER_SIZE 300
#define MAX_COMMAND_LENGTH 50

//custom types
struct JobMessage{//message to be passed between server/client
    char type;//T = trans, D = Done
    int value;
};
typedef struct JobMessage JobMessage;

//common includes
#include "commonStats.c"