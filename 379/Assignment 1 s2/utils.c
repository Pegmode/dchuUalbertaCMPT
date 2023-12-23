#include "utils.h"

void printUsedResources(){
    //singled out for exit command
    struct rusage usage;
    if(getrusage(RUSAGE_CHILDREN, &usage) == 0){
        long userTime = usage.ru_utime.tv_sec;
        long sysTime = usage.ru_stime.tv_sec;
        printf("User time = %3ld seconds\n", userTime);
        printf("Sys  time = %3ld seconds\n\n", sysTime);
    }
}

void removeSpecialArg(CommandContainer currentCommand){//removes special chars from CommandContainer.args so they can be sent to execvp 
    char* inChar;
    char* outChar;
    char* bgChar;
    for(int i = 0; i < currentCommand.argCount; i++){
        bgChar = strchr(currentCommand.args[i], '&');//look for &
        inChar = strchr(currentCommand.args[i], '<');
        outChar = strchr(currentCommand.args[i], '>');
        if((bgChar != NULL) || (inChar != NULL) || (outChar != NULL)){
            currentCommand.args[i] = NULL;
            return;
        }
    }
}

void checkForRedirect(char redirectChar, CommandContainer currentCommand, char* fileName){//find fileName for a given redirection character (> or <) 
    char* specialChar;
    for(int i = 0; i < currentCommand.argCount; i++){
        specialChar = strchr(currentCommand.args[i], redirectChar);//look for file to stdin
        if(specialChar != NULL){
            strcpy(fileName, specialChar + 1);
            return;
        }
    }
}

pid_t execProcess(CommandContainer currentCommand, char* inputFile, char* outputFile, bool isBG){//execute child, return PID if any
    pid_t pid;
    removeSpecialArg(currentCommand);
    if ((pid = fork()) < 0) perror("Error creating fork"); //spawn child
    if(pid == 0){//are we currently child?
        if(inputFile[0] != '\0'){//set stdin in child to file
            int fdi = open(inputFile, O_RDONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);               
            dup2(fdi , STDIN_FILENO);
            close(fdi);
        }
        if(outputFile[0] != '\0'){//set stdout and stderr in child to file
            int fdo = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            dup2(fdo, STDOUT_FILENO);
            dup2(fdo, STDERR_FILENO);
            close(fdo);
        }
        execvp(currentCommand.args[0] , currentCommand.args);//overwrite current program and execute
        _exit(1);//return to parent on exec fail
    }
    else if((pid > 0) && (isBG == false)){//valid PID, we are parent
        wait(NULL);//wait for child if we are parent and no bg flag
    }
    return pid;
}

struct PTableLookupResult lookupInPTable(pid_t pid){//check if pid is in pTable
    struct PTableLookupResult results;
    results.isFound = false;
    for(int i = 0; i < pTable.count; i++){
        if(pTable.processTable[i].pid == pid){
            results.isFound = true;
            results.position = i;
            return results;
        }
    }
}

bool killProcess(pid_t pid){//kill a given process
    struct PTableLookupResult lookupResult = lookupInPTable(pid);
    if(lookupResult.isFound == false){
        printf("Error pid %i not running\n", pid);
        return false;
    }
    if(lookupResult.position > pTable.count){//error check and sanity check
        printf("Error reuquested ptable delete position is outside ptable");
        return false;
    }
    if(kill(pid, SIGKILL) != 0){
        printf("Error in killing process with pid %i\n",pid);
    }
    //update pTable
    for(int i = lookupResult.position; i < pTable.count; i ++){
        pTable.processTable[i] = pTable.processTable[i + 1];
    }
    pTable.count--;
    return true;
}

void killAllProcesses(){
    for(int i = 0; i < pTable.count; i++){
        pid_t pid = pTable.processTable[i].pid;
        if(kill(pid, SIGKILL) != 0){
            printf("Error in killing process with pid %i\n",pid);
        }
    }
    pTable.count = 0;
}

int getCPUTimeFromPID(pid_t pid){//use the ps command to get process cputime
    FILE* pf;
    char command[LINE_LENGTH];
    char psOutput[LINE_LENGTH];
    //run ps command
    sprintf(command, "ps -ho cputimes -p %d", pid);//setup ps command
    if((pf = popen(command, "r")) == NULL ){
        perror("Error unable open pipe to ps\n");
        return -1;
    }
    //get ps output from pipe
    fscanf(pf, "%s", psOutput);
    fgetc(pf);
    pclose(pf);
    //format time return from ps
    int time = atoi(psOutput);
    return time;

}