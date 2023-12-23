//Assignment 1
//CMPUT 379 F2021
//Daniel Chu 1493374

//Referenced much of my own code from F2020 CMPUT 379 
//Referenced Lab 3 F2021
//Referenced in class slides

#include "main.h"



//functions

void inputHandler(char* input){//print input prompt and get input from user
    printf("SHELL 379: ");
    fgets(input, LINE_LENGTH, stdin);
    char* newLineAdr;
    if ((newLineAdr = strchr(input, '\n')) != NULL){
        *newLineAdr = '\0';//add null termination to input string in place of newline
    }
    else{
        printf("ERROR REMOVING NEWLINE!\n");
        abort();
    }
    return;
}

void handleCommand(CommandContainer currentCommand){
    if(currentCommand.argCount == 0){//check for empty input
        return;
    }

    int commandOffset = checkForCommand(currentCommand);
    switch(commandOffset){
        case 0:
            commandExit();
            break;
        case 1:
            commandJobs();
            break;
        case 2://kill
            commandKill(currentCommand);
            break;
        case 3://resume
            commandResume(currentCommand);
            break;
        case 4://sleep
            commandSleep(currentCommand);
            break;
        case 5:
            commandSuspend(currentCommand);
            break;
        case 6:
            commandWait(currentCommand);
            break;
        case -1://command
            commandRun(currentCommand);

            break;
    }
}

int main(){
    char inputString[LINE_LENGTH];
    pTable.count = 0;

    while(1){//Main loop
        inputHandler(inputString);
        CommandContainer currentCommand =  buildCommandContainer(inputString);
        handleCommand(currentCommand);
    }

    return 0;
}