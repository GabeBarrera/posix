/**
 * mizzo.c
 * 
 * The driver file. Initializes semaphores, threads,
 * producers and consumers. When the factory
 * production is complete, a report is generated. 
 */

#include "mizzo.h"

/**
 * MAIN
 *
 * Run "make" and execute "./mizzo".
 * Can pass the following flags:
 * -E [num]		Ethel's ms delay
 * -L [num]		Lucy's ms delay
 * -e [num]		Escargot ms delay
 * -f [num]		Frog Bite ms delay
 */ 
int main (int argc, char *argv[]) {
	int flag;

	buffer *critical_sect = malloc(sizeof(buffer));

	// Initialize totals and counters all to 0
	critical_sect->beltCount = critical_sect->numFrogs = critical_sect->numEscargot = 
	critical_sect->prodTot = critical_sect->consTot = 0;

	producer *frogBite = malloc(sizeof(producer));
	frogBite->critical_sect = critical_sect;
	frogBite->produced = frogBite->msDelay = 0;
	// frogBite->name = "frog bite";
	frogBite->type = "frog bite";

	producer *escargot = malloc(sizeof(producer));
	escargot->critical_sect = critical_sect;
	escargot->produced = escargot->msDelay = 0;
	// escargot->name = "escargot";
	escargot->type = "escargot";

	consumer *lucy = malloc(sizeof(consumer));
	lucy->critical_sect = critical_sect;
	lucy->frogBiteConsumed = lucy->escargotConsumed = lucy->msDelay = 0;
	lucy->name = "Lucy";

	consumer *ethel = malloc(sizeof(consumer));
	ethel->critical_sect = critical_sect;
	ethel->frogBiteConsumed = ethel->escargotConsumed = ethel->msDelay = 0;
	ethel->name = "Ethel";

	// Checking optional command line arguments
	while ((flag = getopt(argc, argv, "E:L:f:e:")) != -1) {
		switch(flag) {
			case 'E':
				ethel->msDelay = atoi(optarg);
				break;
			case 'L':
				lucy->msDelay = atoi(optarg);
				break;
			case 'f':
				frogBite->msDelay = atoi(optarg);
				break;
			case 'e':
				escargot->msDelay = atoi(optarg);
				break;
			case '?':
				printf("\n Error: -E [n] -L [n] -e [n] -f [n] \n");
			default:
				exit(0);
		}
	}

	pthread_t producerThread, consumerThread;
	pthread_t frogThread, escargotThread, lucyThread, ethelThread;

	// Initialize semaphores
	sem_init(&critical_sect->filledSpace, 0, 0);
	sem_init(&critical_sect->freeSpace, 0, BELT_MAX);
	sem_init(&critical_sect->frogSem, 0, FROG_MAX);
	sem_init(&critical_sect->barrierSem, 0, 0);

	// Initialize mutexes
	pthread_mutex_init(&critical_sect->mutex, NULL);

	// Producer Threads
	pthread_create(&frogThread, NULL, produceCandy, (void*) frogBite);
	pthread_create(&escargotThread, NULL, produceCandy, (void*) escargot);

	// Consumer Threads
	pthread_create(&ethelThread, NULL, consumeCandy, (void*) ethel);
	pthread_create(&lucyThread, NULL, consumeCandy, (void*) lucy);

	// Production Output
	sem_wait(&critical_sect->barrierSem);
	printf("\nPRODUCTION REPORT\n");
	printf("------------------------------------------\n");
	printf("Crunchy Frog Bite producer generated %d candies\n", frogBite->produced);
	printf("Escargot Sucker producer generated %d candies\n", escargot->produced);
	printf("Lucy consumed %d Crunchy Frog Bites + %d Escargot Suckers = %d\n", lucy->frogBiteConsumed, lucy->escargotConsumed, lucy->frogBiteConsumed + lucy->escargotConsumed);
	printf("Ethel consumed %d Crunchy Frog Bites + %d Escargot Suckers = %d\n", ethel->frogBiteConsumed, ethel->escargotConsumed, ethel->frogBiteConsumed + ethel->escargotConsumed);

	free(lucy);
	free(ethel);
	free(escargot);
	free(frogBite);
	free(critical_sect);

	exit(0);
}