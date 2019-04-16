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
	// Counters
	int beltCount;
	int numFrogs;
	int numEscargot;
	// Totals
	int prodTot;
	int consTot;
	// Conveyor Belt
	int conveyor_belt[BELT_MAX];
	// Semaphores
	sem_t filledSpace;			// Items produced
	sem_t freeSpace;			// remaining space
	sem_t frogSem;				// Frogs on conveyor belt
	sem_t barrierSem;			// Used for waiting production report

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
	int consumeFB;
	int consumeES;
	char *name;
} consumer;

void *candyProducer(void *c); // Producer function
void *candyConsumer(void *w); // Consumer function

#endif