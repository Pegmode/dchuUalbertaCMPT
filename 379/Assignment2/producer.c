#define MAX_INPUT_BUFFER 100

void addJobToQueue(int cmd, int param, WorkQueue* queue){
    JobRequest* job = (JobRequest*) malloc(sizeof(JobRequest));
    job->type = cmd;
    job->parameter = param;
    
    pthread_mutex_lock(&queue->mutexLock);

    while(isQueueFull(queue)){//wait for queue to have space for new job
        pthread_cond_wait(&queue->isFullCond, &queue->mutexLock);
    }
    enqueue(job, queue);
    logWork(0, queue->size, param);
    pthread_mutex_unlock(&queue->mutexLock);
}

bool readJobInputLine(WorkQueue* queue){//read one job from STDIN, returns false when all lines have been read
    char buffer[MAX_INPUT_BUFFER];
    int cmd, param;
    if(fgets(buffer, MAX_INPUT_BUFFER, stdin) == NULL){//end of file
        return false;
    }
    if(buffer[0] == '\n'){//only for my own input/testing. May remove later
        return false;
    }
    //check command/param
    if(buffer[0] == 'T'){
        cmd = 0;
        param = atoi(&buffer[1]);
        addJobToQueue(cmd, param, queue);
    }
    else if(buffer[0] == 'S'){
        cmd = 1;
        param = atoi(&buffer[1]);
        //addJobToQueue(cmd, param, queue);
        logSleep(0, param);
        Sleep(param);
    }
    else{
        printf("ERROR malformatted input command! \nnote: command is case sensitive\n");
        exit(1);
    }

    return true;
}


void* producer(void *args_p){
    WorkQueue* queue = (WorkQueue*) args_p;

    bool isProducing = true;
    while(isProducing){
        isProducing = readJobInputLine(queue);
        pthread_cond_signal(&queue->isEmptyCond);//signal waiting threads that we have added a job
    }
    pthread_mutex_lock(&queue->mutexLock);
    queue->producingWork = false;
    pthread_mutex_unlock(&queue->mutexLock);
    pthread_cond_broadcast(&queue->isEmptyCond);//signal waiting threads that there is nothing left to work on
    logEnd(0);
}


