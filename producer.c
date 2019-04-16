/**
 * producer.c
 * 
 * Gabriel Barrera
 * Tara Vu
 * Professor Roch
 * CS 570
 * Due Date: 04/16/19
 * 
 * Factory production. Frog Bite and Escargot Sucker producers
 * make candies and put them onto the conveyor belt. This is
 * done in a while loop untl the max num of candies is produced.
 * Data struct info is passed in to specify the type of candy a 
 * producer is supposed to make.
 */
#include "mizzo.h"

void *candyProducer (void *conveyor) {
	producer *Producer = (producer *)conveyor;
	buffer *critSectProducer = Producer->critical_sect;
	int candyMade = 0; // Num of candy made
	int producing = 1; // While loop variable
	char *candyName = Producer->type; // Type of candy to produce
	__useconds_t sleepTime; // Delay
	sleepTime = (__useconds_t) (Producer->msDelay * MS);

	while (producing) {
		// Produce Item
		if (strcmp(candyName, "frog bite") == 0)
			candyMade = FROG_BITE;
		else if (strcmp(candyName, "escargot") == 0)
			candyMade = ESCARGOT;

		sem_wait(&critSectProducer->freeSpace); 		// Lock empty space
		pthread_mutex_lock(&critSectProducer->mutex); 	// Entering critical section
			if (critSectProducer->prodTot < CANDY_TOTAL) {

				// Produce Frog Bites
				if (candyMade == FROG_BITE) {
					pthread_mutex_unlock(&critSectProducer->mutex);
					sem_wait(&critSectProducer->frogSem);
					pthread_mutex_lock(&critSectProducer->mutex);
					critSectProducer->conveyor_belt[critSectProducer->beltCount++] = candyMade;
					critSectProducer->numFrogs++;
				}

				// Produce Escargot Suckers
				else if (candyMade == ESCARGOT) {
					critSectProducer->conveyor_belt[critSectProducer->beltCount++] = candyMade;
					critSectProducer->numEscargot++;
				}

				// Update Production and Local Thread Counters
				critSectProducer->prodTot++;
				Producer->produced++;
				
				// Output
				printf("Belt: %d frogs + %d escargots = %d. produced: %d\t", 
					critSectProducer->numFrogs, critSectProducer->numEscargot, 
					critSectProducer->beltCount, critSectProducer->prodTot);
				if (candyMade == FROG_BITE)
					printf("Added crunchy frog bite.\n");
				else if (candyMade == ESCARGOT)
					printf("Added escargot sucker.\n");
				fflush(stdout);
			} else producing = 0;

		pthread_mutex_unlock(&critSectProducer->mutex);	// Exiting critical section
		sem_post(&critSectProducer->filledSpace);		// Unlock filled space
		usleep(sleepTime); // Sleep
	}

	pthread_exit(NULL);
}