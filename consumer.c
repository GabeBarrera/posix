#include "mizzo.h"

// Consumer 
void *candyConsumer (void *w) {
	consumer *Consumer = (consumer *)w;
	buffer *consumerCritSection = Consumer->critical_sect;
	int candyConsumed = 0, i;
	int loop = 1;
	__useconds_t sleepTime;
	sleepTime = (__useconds_t) (Consumer->msDelay * MS);
	
	while (loop) {
		sem_wait(&consumerCritSection->filledSpace);		// Decrement full count
		pthread_mutex_lock(&consumerCritSection->mutex);	// Enter critical section
			if (consumerCritSection->consTot < CANDY_TOTAL) {

				// Candy is first item off of conveyor belt
				candyConsumed = consumerCritSection->conveyor_belt[0];

				// Rearrange conveyor_belt
				for (i=0; i<consumerCritSection->beltCount; i++)
					consumerCritSection->conveyor_belt[i] = consumerCritSection->conveyor_belt[i+1];
				consumerCritSection->beltCount--;

				// Handle Frog Bites
				if (candyConsumed == FROG_BITE) {
					sem_post(&consumerCritSection->frogSem);
					consumerCritSection->numFrogs--;
				}

				// Handle Escargot Suckers
				else if (candyConsumed == ESCARGOT) 
					consumerCritSection->numEscargot--;

				// Update counters
				consumerCritSection->consTot++;

				// Update local thread counters
				if (candyConsumed == FROG_BITE)
					Consumer->consumeFB++;
				else if (candyConsumed == ESCARGOT)
					Consumer->consumeES++;

				// Output
				printf("Belt: %d frogs + %d escargots = %d. produced: %d\t", 
					consumerCritSection->numFrogs, consumerCritSection->numEscargot, 
					consumerCritSection->beltCount, consumerCritSection->prodTot);
				if (candyConsumed == FROG_BITE)
					printf("%s consumed crunchy frog bite.\n", Consumer->name);
				else if (candyConsumed == ESCARGOT)
					printf("%s consumed escargot sucker.\n", Consumer->name);
				fflush(stdout);
			} else {
				loop = 0;
				sem_post(&consumerCritSection->barrierSem); // Barrier semaphore in main thread
			}

		pthread_mutex_unlock(&consumerCritSection->mutex);	// Exit critical region
		sem_post(&consumerCritSection->freeSpace);			// Increment count of empty slots

		usleep(sleepTime); // Sleep
	}

	pthread_exit(NULL);
}