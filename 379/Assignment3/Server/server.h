#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <signal.h>
#include <stdint.h>
#include <errno.h>


//constants
#define MAX_HOST_NAME 50
#define MAX_CLIENTS 50
#define TIMER_PERIOD 30

//globals
int g_server_transaction_count = 0;//number of total transactions used for transaction ID
pid_t g_pid;
char g_hostname[MAX_HOST_NAME];
double g_start_time;



//custom types
struct ClientTrack{//entry for a single client
    int count;//number of transactions
    char name[MAX_HOST_NAME];
};
typedef struct ClientTrack ClientTrack;

struct ClientsList{//stores clients
    int count;//number of clients
    ClientTrack** clients;
};
typedef struct ClientsList ClientsList;

//global custom type
ClientsList g_clients_list;

//external source files
#include "../common/common.h"
#include "../common/utils.c"
#include "../common/tands.c"
#include "serverStats.c"
#include "clientsList.c"
