#include <stdio.h>
#include <stdlib.h>


//Functions for interacting with WorkQueues and JobRequests

int enqueue(JobRequest* job, WorkQueue* queue){
    if(queue->size != queue-> maxSize){
        queue->size++;
        queue->queue[queue->tail] = job;
        queue->tail = (queue->tail + 1) % queue->maxSize;
        return 1;
    }
    else{
        return -1;//queue is full
    }
}

JobRequest* dequeue(WorkQueue* queue){
    if(queue->size != 0){
        int currentHead = queue->head;
        queue->size--;
        queue->head = (queue->head + 1) % queue->maxSize;
        return queue->queue[currentHead];
    }
    else{//shouldn't hit this if we are checking before calling but lets keep this just in case
        printf("ERROR: tried to dequeue an empty queue");
    }
}

WorkQueue* initQueue(int maxSize){
    WorkQueue* queue = (WorkQueue*) malloc(sizeof(WorkQueue));
    queue->maxSize = maxSize;
    queue->size = 0;
    queue->head = 0;
    queue->tail = 0;
    queue->producingWork = true;
    queue->queue = (JobRequest**) malloc(sizeof(JobRequest)*maxSize);
    pthread_mutex_init(&queue->mutexLock, NULL);
    pthread_cond_init(&queue->isFullCond, NULL);
    pthread_cond_init(&queue->isEmptyCond, NULL);
    return queue;
}

bool isQueueEmpty(WorkQueue* queue){
    return queue->size == 0;
}

bool isQueueFull(WorkQueue* queue){
    return queue->size == queue-> maxSize;
}

JobRequest* createJobRequest(int type, int param){
    JobRequest* job = (JobRequest*) malloc(sizeof(JobRequest));
    job->type = type;
    job->parameter = param;
    return job;
 }