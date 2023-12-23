//CMPUT 379 assignment 2 F21
//Daniel Chu
#include "main.h"

/*
	Synchronization method chosen: Mutex Locks
		Mutex locks provide a simpler implementation but can results in long
		periods where threads are blocked if they are held for long
		periods of time by other threads. Implemented for both file I/O, stats and
		queue access.
*/

int main(int argc, char* argv[]){
	//parse program args
	int consumerCount, id = -1;//id:-1 means no id given
	parseProgArgs(argc, argv, &consumerCount, &id);
	buildLogString(id, g_logFilename);
	//setup queue, stats and mutexs
	WorkQueue* queue = initQueue(2*consumerCount);//initialize work queue
	pthread_mutex_init(&g_fileLock, NULL);//initialize file i/o lock
	g_baseClock = clock();//initialize base time for log
	g_endStats = endStatsInit(consumerCount);
	pthread_mutex_init(&g_endStats->mutexLock, NULL);//initialize stats tracking lock

	clearLogFile();

	//create threads
	pthread_t* consumersT =  (pthread_t*)malloc(sizeof(pthread_t) * consumerCount);
	pthread_t producerT;
	pthread_create(&producerT, NULL, (void*)producer, (void*)queue);

	for(int i = 0; i < consumerCount; i++){
		ConsumerArgs* cArgs = (ConsumerArgs*)malloc(sizeof(ConsumerArgs));
		cArgs->id = i+1;
		cArgs->workQueue=queue;
		pthread_create(&consumersT[i], NULL, consumer, (void*)cArgs);
	}

	for(int i = 0; i < consumerCount; i++){
		pthread_join(consumersT[i], NULL);
	}
	pthread_join(producerT, NULL);
	//end program
	generateEndStats();

	//cleanup conds and locks
	pthread_mutex_destroy(&queue->mutexLock);
	pthread_mutex_destroy(&g_endStats->mutexLock);
	pthread_mutex_destroy(&g_fileLock);
	pthread_cond_destroy(&queue->isFullCond);
	pthread_cond_destroy(&queue->isEmptyCond);
	
	return 0;
}
