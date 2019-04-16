#include "mizzo.h"

// Producer file. Production runs inside a while loop
// that is broken once the total items produced
// goes past the given limit (TOTAL_CANDY). Inside the loop,
// it checks for which type of candy is being passed in
// through the data structure, and produces the correct
// one.
void *produceCandy (void *c) {
	producer *Producer = (producer *)c;
	buffer *producerCritSection = Producer->critical_sect;
	int candyMade = 0;
	int loop = 1;
	char *candyName = Producer->type;
	__useconds_t sleepTime;

	sleepTime = (__useconds_t) (Producer->msDelay * MS);

	while (loop) {

		// Produce Item
		if (strcmp(candyName, "frog bite") == 0)
			candyMade = FROG_BITE;
		else if (strcmp(candyName, "escargot") == 0)
			candyMade = ESCARGOT;

		sem_wait(&producerCritSection->freeSpace); 		// Decrement empty count
		pthread_mutex_lock(&producerCritSection->mutex); 	// Enter critical section
			if (producerCritSection->prodTot < CANDY_TOTAL) {

				// Handle Frog Bites
				if (candyMade == FROG_BITE) {
					pthread_mutex_unlock(&producerCritSection->mutex);
					sem_wait(&producerCritSection->frogSem);
					pthread_mutex_lock(&producerCritSection->mutex);
					producerCritSection->storage[producerCritSection->beltCount++] = candyMade;
					producerCritSection->numFrogs++;
				}

				// Handle Escargot Sucker
				else if (candyMade == ESCARGOT) {
					producerCritSection->storage[producerCritSection->beltCount++] = candyMade;
					producerCritSection->numEscargot++;
				}

				// Update Counters
				producerCritSection->prodTot++;

				// Update local thread counter
				Producer->produced++;

				// Output
				printf("Belt: %d frogs + %d escargots = %d. produced: %d\t", 
					producerCritSection->numFrogs, producerCritSection->numEscargot, 
					producerCritSection->beltCount, producerCritSection->prodTot);
				if (candyMade == FROG_BITE)
					printf("Added crunchy frog bite.\n");
				else if (candyMade == ESCARGOT)
					printf("Added escargot sucker.\n");
				fflush(stdout);
			} else loop = 0;

		pthread_mutex_unlock(&producerCritSection->mutex);	// Exit critical region
		sem_post(&producerCritSection->filledSpace);			// Increment count of full slots

		usleep(sleepTime); // Sleep
	}

	pthread_exit(NULL);
}