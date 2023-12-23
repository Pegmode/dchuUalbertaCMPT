#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

//constants
#define MAX_HOST_NAME 30
#define MAX_INPUT_BUFFER 100

//globals
pid_t g_pid;
char g_hostname[MAX_HOST_NAME];
int g_transaction_count = 1;
int g_port;
char g_connection_address[50];//ip address of server

//external source files
#include "../common/common.h"
#include "../common/utils.c"
#include "../common/tands.c"
#include "clientStats.c"