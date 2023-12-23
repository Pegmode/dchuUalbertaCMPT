//code for handling individual commands
#include "commands.h"

void cmdExit(){
    //printf("Exting shell...\n");
    killAllBackgroundProcesses();
    displayResourcesUsed();
    exit(0);
}

void cmdJobs(){
    printf("\nRunning processes:\n");
    int cpuTime;
    if(ptable.count > 0){
        printf(" #    PID S SEC COMMAND\n");
        for(int i = 0;i < ptable.count;i++){
            cpuTime = getProcessCPUTime(ptable.processTable[i].pid);
            printf(" %d:%6d %c %3d %s\n",i,ptable.processTable[i].pid,ptable.processTable[i].status,cpuTime,ptable.processTable[i].literal);
        }
    }
    printf("Processes = %3d active\n",ptable.count);
    displayResourcesUsed();
}

void cmdKill(struct CommandContainer currentRequestStr){
    if(currentRequestStr.count < 2){
        printf("warning no args given\n");
        return;
    }
    pid_t pid = atoi(currentRequestStr.args[1]);
    killProcess(pid);
}

void cmdResume(struct CommandContainer currentRequestStr){
    if(currentRequestStr.count < 2){
        printf("warning no args given\n");
        return;
    }
    pid_t pid = atoi(currentRequestStr.args[1]);
    int pos = searchForPIDPos(pid);
    if(pos >= 0){
        kill(pid,SIGCONT);//send process resume signal
        ptable.processTable[pos].status = 'R';
    }
    else{
        printf("process with pid %d not found\n",pid);
    }
}

void cmdSleep(struct CommandContainer currentRequestStr){//WHY IS THIS NEEDED AS A COMMAND?
    if(currentRequestStr.count < 2){
        printf("warning no args given\n");
        return;
    }
    int sleepTime = atoi(currentRequestStr.args[1]);
    sleep(sleepTime);
}

void cmdSuspend(struct CommandContainer currentRequestStr){
    if(currentRequestStr.count < 2){
        printf("warning no args given\n");
        return;
    }
    pid_t pid = atoi(currentRequestStr.args[1]);
    int pos = searchForPIDPos(pid);
    if(pos >= 0){
        kill(pid,SIGSTOP);//send process stop signal
        ptable.processTable[pos].status = 'S';
    }
    else{
        printf("process with pid %d not found\n",pid);
    }
}

void cmdWait(struct CommandContainer currentRequestStr){
    if(currentRequestStr.count < 2){
        printf("warning no args given\n");
        return;
    }
    int pidStatus;
    pid_t pid = atoi(currentRequestStr.args[1]);
    waitpid(pid,&pidStatus,0);
}

void cmdRun(struct CommandContainer currentRequestStr){
    struct Process cProcess;//temp local process
    pid_t childPID;
    /*
    Better solution for &,<,>
    search the whole string for the first instance of any one of them. Then have that 
    go into some function that can be nested. I don't have time
    to re do half of my assignment to fit this one criteria. 
    */

    //check for redirection
    char* charPtr;
    charPtr = strchr(currentRequestStr.literal,'<');//look for file to stdin
    if(charPtr != NULL){
        //printf("\nDBUG < hit\n\n");
        fileToStdin(currentRequestStr, charPtr + 1) ;
        return;
    }
    charPtr = strchr(currentRequestStr.literal,'>');//look for stdout to file
    if(charPtr != NULL){
        //printf("\nDBUG > hit\n\n");
        stdoutToFile(currentRequestStr,charPtr + 1);
        return;
    }

    //check for BG flag
    bool isBGFlag = checkForArg("&",currentRequestStr.args,currentRequestStr.count);
    if(isBGFlag){
        //cProcess.startTime = time(NULL);
        childPID = spawnChildProcess(currentRequestStr,isBGFlag);//RUN!
        cProcess.pid = childPID;
        cProcess.status = 'R';
        strcpy(cProcess.literal,currentRequestStr.literal);
        //ptable checkout
        memcpy(&ptable.processTable[ptable.count],&cProcess,sizeof(cProcess));//copy temp into ptable
        ptable.count++;

    }
    else{
        spawnChildProcess(currentRequestStr,isBGFlag);
    }

}


