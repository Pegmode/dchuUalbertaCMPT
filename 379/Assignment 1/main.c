//Assignment 1
//University of Alberta CMPUT 279 F2020
//Daniel Chu 1493374

//used in class examples as reference for pipes

#include "main.h"


void inputHanlder(char* string){
    printf("SHELL 379: ");
    fgets(string,LINE_LENGTH,stdin);
    char* newlineAdr;
    if ((newlineAdr = strchr(string, '\n')) != NULL){
        *newlineAdr = '\0';
    }
    else{
        printf("Error removing newline!\n");
        abort();
    }
}

int stringArrayContains(int size,char* stringArray[],char* key){// linear searches string array for key index
    int index = -1;
    int i;
    for(i = 0;i < size;i++){
        if(strcmp(stringArray[i],key) == 0){
            index = i;
        }
    }
    return index;
}

void commandHandler(struct CommandContainer currentRequestStr){
    char* commands[] = {
        "exit",
        "jobs",
        "kill",
        "resume",
        "sleep",
        "suspend",
        "wait"
    };
    //command empty?
    if(currentRequestStr.count == 0){//doesn't run because of scan implementaiton
        //CMDN IS EMPTY
        return;
    }
    //command has contents
    int switchControl;
    int numberOfCommands = sizeof(commands)/sizeof(commands[0]);
    switchControl = stringArrayContains(numberOfCommands,commands,currentRequestStr.args[0]);

    switch (switchControl)
    {
    case 0://exit
        cmdExit();
        break;
    case 1://jobs
        cmdJobs();
        break;
    case 2://kill
        cmdKill(currentRequestStr);
        break;
    case 3://resume
        cmdResume(currentRequestStr);
        break;
    case 4://sleep
        cmdSleep(currentRequestStr);
        break;
    case 5://suspend
        cmdSuspend(currentRequestStr);
        break;
    case 6://wait
        cmdWait(currentRequestStr);
        break;
    case -1://Run command
        //printf("Run Command\n");
        cmdRun(currentRequestStr);
        break;
    default://something went wrong 
        printf("Error parsing command!\n");
        abort();
        break;
    }
    //return to main loop
}

int main(){
    //init
    //printf("SHELL379 \nBy dchu\n");
    char inputString[LINE_LENGTH];
    ptable.count = 0;

    //init Debu
    //22478, 23549
    /*
    printf("dbug:WORKING %d\n",checkPID(22478));
    printf("dbug:WORKING %d\n",checkPID(23549));
    printf("dbug:NWORKING %d\n",checkPID(42069));
    */

    while (1){//main loop
        inputHanlder(inputString);
        struct CommandContainer currentCommandString = buildCMDContainer(inputString);
        scanPTableForQuitters();
        commandHandler(currentCommandString);
        //loop debug

    }
    printf("WARNING: Program hit bottom of main\n");
}