#include "commands.h"

void commandExit(){
    killAllProcesses();
    printUsedResources();
    exit(0);
}

void commandJobs(){
    int cpuTime;
    printf("\nRunning processes:\n #    PID S SEC COMMAND\n");
    for(int i = 0; i < pTable.count; i++){
        cpuTime = getCPUTimeFromPID(pTable.processTable[i].pid);
        printf(" %d:%6d %c %3d %s\n" , i, pTable.processTable[i].pid ,pTable.processTable[i].status ,cpuTime ,pTable.processTable[i].command);
    }
    printf("Processes = %3d active\n", pTable.count);
    printUsedResources();
}

void commandKill(CommandContainer currentCommand){
    if(currentCommand.argCount < 2){
        printf("Error kill command requires single arguement\n");
        return;
    }
    pid_t pid = atoi(currentCommand.args[1]);
    killProcess(pid);
}

void commandResume(CommandContainer currentCommand){
    if(currentCommand.argCount < 2){
        printf("Error resume command requires single arguement\n");
        return;
    } 
    pid_t pid = atoi(currentCommand.args[1]);
    struct PTableLookupResult lookupResult = lookupInPTable(pid);
    if(lookupResult.isFound == false){
        printf("Error pid %d not found\n", pid);
        return;
    }
    kill(pid, SIGCONT);
    pTable.processTable[lookupResult.position].status = 'R';
}

void commandSleep(CommandContainer currentCommand){
    if(currentCommand.argCount < 2){
        printf("Error sleep command requires single arguement\n");
        return;
    } 
    sleep(atoi(currentCommand.args[1]));
}

void commandSuspend(CommandContainer currentCommand){
    if(currentCommand.argCount < 2){
        printf("Error suspend command requires single arguement\n");
        return;
    }
    pid_t pid = atoi(currentCommand.args[1]);
    struct PTableLookupResult lookupResult = lookupInPTable(pid);
    if(lookupResult.isFound == false){
        printf("Error pid %d not found\n", pid);
        return;
    }
    kill(pid, SIGSTOP);
    pTable.processTable[lookupResult.position].status = 'S';
}

void commandWait(CommandContainer currentCommand){
    if(currentCommand.argCount < 2){
        printf("Error wait command requires single arguement\n");
        return;
    }
    pid_t pid = atoi(currentCommand.args[1]);
    struct PTableLookupResult lookupResult = lookupInPTable(pid);
    if(lookupResult.isFound == false){
        printf("Error pid %d not found\n", pid);
        return;
    }
    int status;
    waitpid(pid, &status, 0);
}

void commandRun(CommandContainer currentCommand) {
    //checks and init for redirection
    //if inputFile or outputFile first entry == '\0', then there is no redirection
    char inputFile[LINE_LENGTH] = {'\0'};
    char outputFile[LINE_LENGTH] = {'\0'};
    checkForRedirect(REDIRECT_STDIN, currentCommand, inputFile);
    checkForRedirect(REDIRECT_STDOUT, currentCommand, outputFile);
    //setup BG
    
    Process process;
    char* charPtr;
    charPtr = strchr(currentCommand.literal,RUN_BG);
    if(charPtr != NULL){//if is bg flag (&)
        pid_t pid = execProcess(currentCommand, inputFile, outputFile, true);
        //add process to pTable
        process.pid = pid;
        strcpy(process.command, currentCommand.literal);
        process.status = 'R';
        pTable.processTable[pTable.count];
        pTable.count++;
        printf("\n\nPTABLE IN %i\n\n", pTable.count);
    }
    else{//if not bg flag (&)
        execProcess(currentCommand, inputFile, outputFile, false);
    }

}
