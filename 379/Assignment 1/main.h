#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <signal.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/time.h>


//main header
#define LINE_LENGTH 100 // Max # of characters in an input line
#define MAX_ARGS 8 // Max number of arguments to a command added + 1
#define MAX_LENGTH 20 // Max # of characters in an argument
#define MAX_PT_ENTRIES 32 // Max entries in the Process Tabl



//structs
struct CommandContainer {
    char literal[LINE_LENGTH];
    char ** args;//command request args
    int count;//number of args
};
struct Process{//Process entry for Process Table
    pid_t pid;
    char literal[LINE_LENGTH];
    char status;//R or S
};

struct ProcessTable{//Process Control Block
    int count;
    struct Process processTable[MAX_PT_ENTRIES];
}ptable;//global var

struct ComptletedTimeContainer{
    int long user;
    int long sys;
    
}completedTime = {0,0};

//source
#include "commands.c"
#include "utils.c"

