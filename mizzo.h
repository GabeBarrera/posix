#ifndef MIZZO_H
#define MIZZO_H
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CANDY_TOTAL 100		// Max items allowed to be produced
#define BELT_MAX 10			// Max items allowed on belt
#define FROG_MAX 3			// Max frogs allowed on belt
#define FROG_BITE 1			// Define frog bite
#define ESCARGOT 0			// Define escargot
#define MS 1000				// 1000 microseconds per 1 ms

typedef struct {
	int storage[BELT_MAX];		// conveyor belt storage

	// Counters
	int beltCount;
	int numFrogs;
	int numEscargot;

	// Totals
	int prodTot;
	int consTot;

	// Semaphores
	sem_t filledSpace;			// Items produced
	sem_t freeSpace;			// remaining space
	sem_t frogSem;				// Frogs on conveyor belt
	sem_t barrierSem;

	// Mutexes
	pthread_mutex_t mutex;		// Protects the counters
} buffer;

// Producer Struct (for Frog Bites & Escargot)
typedef struct {
	buffer *critical_sect;
	int produced;
	int msDelay;
	char *type;
} producer;

// Consumer Struct (for Ethel & Lucy)
typedef struct {
	buffer *critical_sect;
	int msDelay;
	int frogBiteConsumed;
	int escargotConsumed;
	char *name;
} consumer;

void *produceCandy (void *c);

void *consumeCandy (void *w);

#endif