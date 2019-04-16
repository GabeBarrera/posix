#ifndef MIZZO_H
#define MIZZO_H

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for sleep
#include <string.h> //for string compare

#define FROG_MAX 3
#define BELT_MAX 10		// Total items on conveyor belt at once
#define CANDY_TOTAL 100		// Total items produced by a candy generator

#define FROG_BITE 1
#define ESCARGOT 0

#define MS 1000			// One thousand microseconds per milliseconds

typedef struct {
	int storage[BELT_MAX];		// conveyor belt storage

	// Counters
	int beltCount;
	int frogCount;
	int escargotCount;
	int barrierCount;

	// Totals
	int totalProduced;
	int totalConsumed;

	// Semaphores
	sem_t fillCount;			// Items produced
	sem_t emptyCount;			// remaining space
	sem_t frogSem;				// Frogs on conveyor belt
	sem_t barrierSem;

	// Mutexes
	pthread_mutex_t mutex;		// Protects the counters
} semBuffer;

typedef struct {
	semBuffer *crit_section;
	int produced;
	int duration;
	char *name;
} producer;

typedef struct {
	semBuffer *crit_section;
	int duration;
	int frogBiteConsumed;
	int escargotConsumed;
	char *name;
} consumer;

void *produceCandy (void *c);

void *consumeCandy (void *w);

#endif