/**
 * consumer.c
 * 
 * Gabriel Barrera
 * Tara Vu
 * Professor Roch
 * CS 570
 * Due Date: 04/16/19
 * 
 * Candy consumption. Ethel and Lucy consume the candy
 * produced until the last candy is consumed. Data
 * struct passed in to specify who is currently consuming. 
 */
#include "mizzo.h"

void *candyConsumer (void *worker) {
	consumer *Consumer = (consumer *)worker;
	buffer *critSectConsumer = Consumer->critical_sect;
	int candyConsumed = 0; // Candy Type
	int i; // Var for moving next item in conveyor belt
	int consuming = 1; // While loop variable
	__useconds_t sleepTime; // Delay
	sleepTime = (__useconds_t) (Consumer->msDelay * MS);
	
	while (consuming) {
		sem_wait(&critSectConsumer->filledSpace);		// Lock filled space
		pthread_mutex_lock(&critSectConsumer->mutex);	// Entering critical section
			if (critSectConsumer->consTot < CANDY_TOTAL) {

				// Next candy to consume is the first one on the belt
				candyConsumed = critSectConsumer->conveyor_belt[0];

				// Move conveyor_belt along in FIFO order
				for (i=0; i<critSectConsumer->beltCount; i++)
					critSectConsumer->conveyor_belt[i] = critSectConsumer->conveyor_belt[i+1];
				critSectConsumer->beltCount--;

				// Consume Frog Bites
				if (candyConsumed == FROG_BITE) {
					sem_post(&critSectConsumer->frogSem);
					critSectConsumer->numFrogs--;
				}

				// Consume Escargot Suckers
				else if (candyConsumed == ESCARGOT) 
					critSectConsumer->numEscargot--;

				// Update Consumer and Local Thread counters
				critSectConsumer->consTot++;
				if (candyConsumed == FROG_BITE)
					Consumer->consumeFB++;
				else if (candyConsumed == ESCARGOT)
					Consumer->consumeES++;

				// Output
				printf("Belt: %d frogs + %d escargots = %d. produced: %d\t", 
					critSectConsumer->numFrogs, critSectConsumer->numEscargot, 
					critSectConsumer->beltCount, critSectConsumer->prodTot);
				if (candyConsumed == FROG_BITE)
					printf("%s consumed crunchy frog bite.\n", Consumer->name);
				else if (candyConsumed == ESCARGOT)
					printf("%s consumed escargot sucker.\n", Consumer->name);
				fflush(stdout);
			} else {
				consuming = 0;
				sem_post(&critSectConsumer->inProduction);
			}

		pthread_mutex_unlock(&critSectConsumer->mutex);	// Exiting critical section
		sem_post(&critSectConsumer->freeSpace);			// Unlock free space
		usleep(sleepTime); // Sleep
	}

	pthread_exit(NULL);
}