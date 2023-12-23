#include "inputUtils.h" 



CommandContainer buildCommandContainer(char* commandString){//parse a string and build a CommandContainer from the string
    char** parsedCommands;
    CommandContainer currentCommand;
    strcpy(currentCommand.literal, commandString);
    //alloc for args
    currentCommand.args = malloc((MAX_ARGS+1) *     sizeof(char*));
    for(int i = 0; i < (MAX_ARGS + 1); i++){
        currentCommand.args[i] = malloc(LINE_LENGTH * sizeof(char));
    }

    char* subString;
    subString = strtok(commandString, " ");//copy first arg to substring
    int i = 0;

    while (subString != NULL){//
        strcpy(currentCommand.args[i], subString);
        subString = strtok(NULL, " ");
        i++;
    }

    currentCommand.args[i] = NULL;//needed for exevp()
    currentCommand.argCount = i;


    return currentCommand;
}

int checkForCommand(CommandContainer currentCommand){//parses currentCommand for valid command and returns the offset in COMMANDS 
    for(int i = 0; i < COMMANDS_COUNT; i++){
        if(strcmp(COMMANDS[i], currentCommand.args[0]) == 0){
            return i;
        }
    }
    return -1;
}

bool checkForArgValue(char* string, int startPos, CommandContainer currentCommand){//check currentCommand args for instance of given string starting at position
    for(int i = startPos; i < currentCommand.argCount; i++){
        if(strcmp(string, currentCommand.args[i]) == 0){
            return true;
        }
    }
    return false;
}

