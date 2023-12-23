#include "utils.h"

pid_t spawnChildProcess(struct CommandContainer currentRequestStr,bool isBG){//run command
    pid_t childPID;
    childPID = fork();
    if((childPID == 0)){//if we are child 
        if(isBG){//remove & from args
            //signal(SIGABRT,killSignalHandler);
            currentRequestStr.args[currentRequestStr.count - 1] = NULL;  
        }
        execProcess(currentRequestStr);
        _exit(1);//exits in bad case
    }
    else if (isBG == false){//fg process
        wait(NULL);//wait for child to finish
    }
    else{//if bg
        //signal(SIGCHLD,SIG_IGN);
    }
    
    return childPID;//if parent, return pid
}


void execProcess(struct CommandContainer currentRequestStr){
    if(execvp(currentRequestStr.args[0],currentRequestStr.args)< 0){
        perror("Execution Error:");
    }
}

struct CommandContainer buildCMDContainer(char* cmdString){
    char** parsedStrings;
    struct CommandContainer parsedStr;
    strcpy(parsedStr.literal,cmdString);
    parsedStr.args = malloc((MAX_ARGS+1)*sizeof(char*));//parsed args setup
    
    for(int i = 0; i < (MAX_ARGS+1);i++){
        parsedStr.args[i] = malloc(MAX_LENGTH*sizeof(char));
    }

    char* subString;
    subString = strtok(cmdString," ");//copy first arg  
    int i = 0;

    while(subString != NULL){//store and parse all args
        strcpy(parsedStr.args[i],subString);
        subString = strtok(NULL," ");
        i++;
    }
    parsedStr.args[i] = NULL;
    parsedStr.count = i;
    return parsedStr;
}

bool checkForArg(char* argKey, char ** argList,int size){//linear search for arg
    for(int i = 0; i < size;i++){
        if(strcmp(argKey,argList[i]) == 0){
            return true;
        }
    }
    return false;
}


int searchForPIDPos(pid_t pid){//search ptable for pid and return index
    for(int i = 0;i < ptable.count;i++){//linear serach for pos
        if(ptable.processTable[i].pid == pid){
            return i;
        }
    }
    return -1;

}

bool removeFromPTable(pid_t pid){
    for(int i = 0;i < ptable.count;i++){//linear serach for pos
        if(ptable.processTable[i].pid == pid){
            ptable.count--;
            for(;i < ptable.count;i++){
                ptable.processTable[i] = ptable.processTable[i+1];
            }
            return true;
        }
    }
    return false;
}

bool killProcess(pid_t pid){
    if(removeFromPTable(pid) == false){
        printf("warning: pid %d not found in table\n",pid);
        return false;
    }
    if(kill(pid,SIGKILL) != 0){//KILL!!
        printf("warning: could not kill process with pid %d\n",pid);
    }
    return true;
}

void displayResourcesUsed(){
    printf("Completed processes:\n");
    struct rusage childRUsage;
    if(getrusage(RUSAGE_CHILDREN,&childRUsage) == 0){
        printf("User time = %3ld seconds\n",childRUsage.ru_utime.tv_sec);
        printf("Sys  time = %3ld seconds\n\n",childRUsage.ru_stime.tv_sec);
        //debug fine timing
        //printf("User time = %3ld uSeconds\n",childRUsage.ru_utime.tv_usec);
        //printf("Sys  time = %3ld uSeconds\n",childRUsage.ru_stime.tv_usec);
    }
}

void killAllBackgroundProcesses(){
    for(int i = 0;i < ptable.count;i++){
        killProcess(ptable.processTable[i].pid);
    }
}


//should make ps pipe open function if I have time
//returns 1 if was success
int readPsPipe(char* buffer,char* command,pid_t pid){
    FILE* pfile;
    char commandBuffer[LINE_LENGTH];
    sprintf(commandBuffer,command,pid);//format command for pipe
    if((pfile = popen(commandBuffer,"r")) == NULL ){
        perror("Could not open pipe to ps\n");
        return 0;
    }
    else{
        fscanf(pfile, "%s", buffer);
        fgetc(pfile);
        pclose(pfile);//online doc does not match notes. Watch out for closure errors.
        return 1;
    }    
}


//gets cpu time from ps
////returns -1 on empty pid
//DO NOT USE TO TEST FOR PROCESS
int getProcessCPUTime(pid_t pid){
    char buffer[LINE_LENGTH];//doesn't HAVE to be LINE_LENGTH but just to be safe
    if(readPsPipe(buffer,"ps -ho cputime -p %d",pid) == 1){
        int time;
        int stringSize = strlen(buffer);
        if(stringSize <= 1){
            printf("Error: PID %d not found\n",pid);
            return -1;
        }
        buffer[stringSize - 3] = '\0';//clip end ps output
        time = atoi(&buffer[3]);//clip beginning ps output
        return time;
    }
    else{
        return -1;
    }
}

int checkPID(pid_t pid){//returns 0 if process doesn't exist,should return 8 if process is running
    char buffer[LINE_LENGTH];//doesn't HAVE to be LINE_LENGTH but just to be safe
    buffer[0] = '\0';//reset
    readPsPipe(buffer,"ps -ho cputime -p %d",pid);
    return strlen(buffer);
}

void scanPTableForQuitters(){//scans ptable for processes that are not running and removes them
    for(int i = 0;i < ptable.count;i++){
        if(checkPID(ptable.processTable[i].pid) == 0){
            //printf("DEBUG: Process %d finished\n",ptable.processTable[i].pid);
            removeFromPTable(ptable.processTable[i].pid);
        }
    }

}

int find1stCharPos(char* string, char key){
    int size = strlen(string);
    for(int i = 0; i < size;i++){
        if(string[i] == key){
            return i;
        }
    }
    return -1;
}

void splitString(struct CommandContainer currentRequestStr,char* commandBuffer, char key){
    int keyPos = find1stCharPos(currentRequestStr.literal,key);
    strcpy(commandBuffer,currentRequestStr.literal);
    commandBuffer[keyPos] = '\0';
}


void fileToStdin(struct CommandContainer currentRequestStr, char* filename){// <
    FILE* f;
    FILE* pfile;

    f = fopen(filename,"r");

    char commandBuffer[LINE_LENGTH];
    splitString(currentRequestStr,commandBuffer,'<');
    //printf("\nDEBUG commandbuffer: %s\n\n",commandBuffer);
    pfile = popen(commandBuffer,"w");
    char interchangeBuffer[LINE_LENGTH];
    while(fgets(interchangeBuffer,LINE_LENGTH,f) != NULL){
        printf("%s",interchangeBuffer);
        fputs(interchangeBuffer,pfile);
    }
    fclose(f);
    pclose(pfile);
}

void stdoutToFile(struct CommandContainer currentRequestStr, char* filename){// >
    FILE* f;
    FILE* pfile;

    f = fopen(filename,"w");

    char commandBuffer[LINE_LENGTH];
    splitString(currentRequestStr,commandBuffer,'>');
    //printf("\nDEBUG commandbuffer: %s\n\n",commandBuffer);
    pfile = popen(commandBuffer,"r");
    char interchangeBuffer[LINE_LENGTH];
    while(fgets(interchangeBuffer,LINE_LENGTH,pfile) != NULL){
        printf("%s",interchangeBuffer);
        fputs(interchangeBuffer,f);
    }
    fclose(f);
    pclose(pfile);

}