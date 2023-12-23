#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h> 
#include <signal.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/time.h>

//Main Const
//(given in assignment)
#define LINE_LENGTH 100 // Max # of characters in an input line
#define MAX_ARGS 7 // Max number of arguments to a command
#define MAX_LENGTH 20 // Max # of characters in an argument
#define MAX_PT_ENTRIES 32 // Max entries in the Process Table

#define COMMANDS_COUNT 7

//special characters
#define REDIRECT_STDIN '<'//
#define REDIRECT_STDOUT '>'
#define RUN_BG '&'

static char* COMMANDS[] = {
    "exit",
    "jobs",
    "kill",
    "resume",
    "sleep",
    "suspend",
    "wait"
};



//main structs
struct CommandContainer{//contains formatted args for handling commands
    char literal[LINE_LENGTH];//string literal containing raw input given for command
    char** args;//list of current arguements (argv)
    int argCount;//argCount (argc)
};
typedef struct CommandContainer CommandContainer;

struct Process{
    pid_t pid;
    char status;
    char command[LINE_LENGTH];

};
typedef struct Process Process;

struct ProcessTable{
    int count;
    Process processTable[MAX_PT_ENTRIES];
};
typedef struct ProcessTable ProcessTable;

//init global process table 
ProcessTable pTable;//moved to global to fix bug



//extern
#include "utils.c"
#include "inputUtils.c"
#include "commands.c"