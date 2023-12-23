#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>


//constants
#define MAX_LOG_FILENAME_SIZE 15 //Max chars - 1

//globals
	//I/O
pthread_mutex_t g_fileLock;//lock for file i/o
char g_logFilename[MAX_LOG_FILENAME_SIZE];
	//Stats
pthread_mutex_t g_statsLock;//lock for keeping track of stats
clock_t g_baseClock;//start time for log comparison

struct EndStats{
	pthread_mutex_t mutexLock;
	int work;
	int ask;
	int receive;
	int complete;
	int sleep;
	int* threads;
	int threadSize;
};
typedef struct EndStats EndStats;
EndStats* g_endStats;//Global variable containing all the end stats

//custom struct types
struct JobRequest{
	int type;//0 = Transaction, 1 = sleep
	int parameter;
};
typedef struct JobRequest JobRequest;

struct WorkQueue{
	pthread_mutex_t mutexLock;//lock for queue
    pthread_cond_t isFullCond;
    pthread_cond_t isEmptyCond;//tests both empty and finished producing
    bool producingWork;
	int head;
	int tail;
    int size;
 	int maxSize;
	JobRequest** queue;
};
typedef struct WorkQueue WorkQueue;

struct ConsumerArgs{
   WorkQueue* workQueue;
   int id; 
};
typedef struct ConsumerArgs ConsumerArgs;

//debug
void printQueue(WorkQueue* q){
	printf("Queue State: producing:%i, size:%i\n",q->producingWork,q->size);
}
void printJob(JobRequest* j){
	char t;
	if(j->type ==0){
		t = 'T';
	}
	else{
		t = 'S';
	}
	printf("Job:%c%i\n",t,j->parameter);
}

//file includes
#include "tands.c"
#include "utils.c"
#include "stats.c"
#include "workQueues.c"
#include "consumer.c"
#include  "producer.c"