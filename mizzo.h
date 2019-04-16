/**
 * mizzo.h
 * 
 * Gabriel Barrera
 * Tara Vu
 * Professor Roch
 * CS 570
 * Due Date: 04/16/19
 * 
 * The header file. Contains all the variable definitons
 * structs, and producer/consumer functions needed for
 * the Mizzo Candy Factory.
 */
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
	// Counters, Totals, and Conveyor Belt
	int beltCount;
	int numFrogs;
	int numEscargot;
	int prodTot;
	int consTot;
	int conveyor_belt[BELT_MAX];
	// Counter Protector
	pthread_mutex_t mutex;		// Aids counter integrity/accuracy during production
	// Semaphores
	sem_t filledSpace;			// Candy produced
	sem_t freeSpace;			// Available space
	sem_t frogSem;				// Frogs on conveyor belt
	sem_t inProduction;			// Used for waiting production report
} buffer;

// Producer Struct (for Frog Bites & Escargot)
typedef struct {
	buffer *critical_sect;
	int msDelay;	// Delay in milliseconds
	int produced;	// Num of candies produced
	char *type;		// Candy ID tag
} producer;

// Consumer Struct (for Ethel & Lucy)
typedef struct {
	buffer *critical_sect;
	int msDelay;	// Delay in milliseconds
	int consumeFB; 	// Frog Bite consumption
	int consumeES; 	// Escargot consumption
	char *name;		// Consumer ID tag
} consumer;

void *candyProducer(void *conveyor); // Producer function
void *candyConsumer(void *worker); // Consumer function

#endif