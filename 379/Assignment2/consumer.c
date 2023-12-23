#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>


void doJob(JobRequest* job){
    if(job->type == 0){
        Trans(job->parameter);
    }
    else if(job->type == 1){
        Sleep(job->parameter);
    }
    else{
        printf("Error incorrect job type given");
    }
}

void* consumer(void* args_p){
    ConsumerArgs* args = (ConsumerArgs*) args_p;
    int id = args->id;
    pthread_mutex_t mutexLock = args->workQueue->mutexLock;
    WorkQueue* queue = args->workQueue;
    bool producingWork = true;

    while(producingWork){
        logAsk(id);
        pthread_mutex_lock(&args->workQueue->mutexLock);
        while(isQueueEmpty(queue) && queue->producingWork){//wait for queue to have work
            pthread_cond_wait(&queue->isEmptyCond, &args->workQueue->mutexLock);//this causes problems
        }

        if(!isQueueEmpty(queue)){//if work exists in queue
            int jobParam;
            JobRequest* job = dequeue(queue);
            jobParam = job->parameter;
            logReceive(id, queue->size, jobParam);
            pthread_mutex_unlock(&args->workQueue->mutexLock);
            pthread_cond_signal(&queue->isFullCond);//tell producer that we are open
            doJob(job);
            logComplete(id, queue->size, jobParam);//report work 
            incEndThreadStat(id);
            //report work
        }

        else if(isQueueEmpty(queue) && !queue->producingWork){//if there is no work and there is no longer production
            pthread_mutex_unlock(&args->workQueue->mutexLock);
            producingWork = false;
            pthread_cond_broadcast(&queue->isEmptyCond);//tell other waiting consumers that we are finished

            //end thread
        }
    }

}