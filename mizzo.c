/**
 * mizzo.c
 * 
 * Gabriel Barrera
 * Tara Vu
 * Professor Roch
 * CS 570
 * Due Date: 04/16/19
 * 
 * The driver file. Initializes semaphores, threads,
 * producers and consumers. When the factory
 * production is complete, a report is generated.
 * 
 * Run "make" and execute "./mizzo".
 * Can pass the following flags:
 * -E [num]		Ethel's ms delay
 * -L [num]		Lucy's ms delay
 * -e [num]		Escargot ms delay
 * -f [num]		Frog Bite ms delay 
 */
#include "mizzo.h"

int main (int argc, char *argv[]) {
	int flag; // For command line flags
	buffer *critical_sect = malloc(sizeof(buffer));

	// Initialize all counters to 0
	critical_sect->numFrogs = critical_sect->numEscargot = 0;
	critical_sect->prodTot = critical_sect->consTot = 0;
	critical_sect->beltCount = 0;

	// Initialize Frog Bite and Escargo Sucker producers
	producer *frogBite = malloc(sizeof(producer));
	frogBite->critical_sect = critical_sect;
	frogBite->produced = frogBite->msDelay = 0;
	frogBite->type = "frog bite";

	producer *escargot = malloc(sizeof(producer));
	escargot->critical_sect = critical_sect;
	escargot->produced = escargot->msDelay = 0;
	escargot->type = "escargot";

	// Initialize Ethel and Lucy consumers
	consumer *ethel = malloc(sizeof(consumer));
	ethel->critical_sect = critical_sect;
	ethel->consumeFB = ethel->consumeES = ethel->msDelay = 0;
	ethel->name = "Ethel";

	consumer *lucy = malloc(sizeof(consumer));
	lucy->critical_sect = critical_sect;
	lucy->consumeFB = lucy->consumeES = lucy->msDelay = 0;
	lucy->name = "Lucy";

	// Optional CLI flgs
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
				printf("\n Error: -E [num] -L [num] -e [num] -f [num] \n");
			default:
				exit(0);
		}
	}
	pthread_t frogThread, escargotThread, lucyThread, ethelThread;

	// Initialize semaphores
	sem_init(&critical_sect->filledSpace, 0, 0);
	sem_init(&critical_sect->freeSpace, 0, BELT_MAX);
	sem_init(&critical_sect->frogSem, 0, FROG_MAX);
	sem_init(&critical_sect->inProduction, 0, 0);

	// Initialize mutex
	pthread_mutex_init(&critical_sect->mutex, NULL);

	// Producer Threads
	pthread_create(&frogThread, NULL, candyProducer, (void*) frogBite);
	pthread_create(&escargotThread, NULL, candyProducer, (void*) escargot);

	// Consumer Threads
	pthread_create(&ethelThread, NULL, candyConsumer, (void*) ethel);
	pthread_create(&lucyThread, NULL, candyConsumer, (void*) lucy);

	// Production Report
	sem_wait(&critical_sect->inProduction); // When factory is done producing, print report
	printf("\nPRODUCTION REPORT\n------------------------------------------\n");
	printf("Crunchy Frog Bite producer generated %d candies\n", frogBite->produced);
	printf("Escargot Sucker producer generated %d candies\n", escargot->produced);
	printf("Lucy consumed %d Crunchy Frog Bites + %d Escargot Suckers = %d\n", lucy->consumeFB, lucy->consumeES, lucy->consumeFB + lucy->consumeES);
	printf("Ethel consumed %d Crunchy Frog Bites + %d Escargot Suckers = %d\n", ethel->consumeFB, ethel->consumeES, ethel->consumeFB + ethel->consumeES);

	// Free all allocated memory and quit program
	free(lucy);
	free(ethel);
	free(escargot);
	free(frogBite);
	free(critical_sect);
	exit(0);
}